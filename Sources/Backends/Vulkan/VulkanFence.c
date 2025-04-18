// Copyright (C) 2025 kanel
// This file is part of "Pulse"
// For conditions of distribution and use, see copyright notice in LICENSE

#include <vulkan/vulkan_core.h>

#include "Vulkan.h"
#include "VulkanDevice.h"
#include "VulkanFence.h"

PulseFence VulkanCreateFence(PulseDevice device)
{
	PULSE_CHECK_HANDLE_RETVAL(device, PULSE_NULL_HANDLE);

	VkFenceCreateInfo fence_info = { 0 };
	fence_info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	fence_info.flags = VK_FENCE_CREATE_SIGNALED_BIT;
	VkFence vulkan_fence;
	VulkanDevice* vulkan_device = VULKAN_RETRIEVE_DRIVER_DATA_AS(device, VulkanDevice*);
	CHECK_VK_RETVAL(device->backend, vulkan_device->vkCreateFence(vulkan_device->device, &fence_info, PULSE_NULLPTR, &vulkan_fence), PULSE_ERROR_INITIALIZATION_FAILED, PULSE_NULL_HANDLE);

	PulseFenceHandler* fence = (PulseFenceHandler*)malloc(sizeof(PulseFenceHandler));
	PULSE_CHECK_ALLOCATION_RETVAL(fence, PULSE_NULL_HANDLE);
	fence->cmd = PULSE_NULL_HANDLE;
	fence->driver_data = vulkan_fence;
	return fence;
}

void VulkanDestroyFence(PulseDevice device, PulseFence fence)
{
	PULSE_CHECK_HANDLE(device);

	if(fence == PULSE_NULL_HANDLE)
	{
		if(PULSE_IS_BACKEND_LOW_LEVEL_DEBUG(device->backend))
			PulseLogWarning(device->backend, "fence is NULL, this may be a bug in your application");
		return;
	}

	VulkanDevice* vulkan_device = VULKAN_RETRIEVE_DRIVER_DATA_AS(device, VulkanDevice*);
	if(vulkan_device == PULSE_NULLPTR || vulkan_device->device == VK_NULL_HANDLE)
		return;
	VkFence vulkan_fence = VULKAN_RETRIEVE_DRIVER_DATA_AS(fence, VkFence);
	if(vulkan_fence == VK_NULL_HANDLE)
		return;
	vulkan_device->vkDestroyFence(vulkan_device->device, vulkan_fence, PULSE_NULLPTR);
	free(fence);
}

bool VulkanIsFenceReady(PulseDevice device, PulseFence fence)
{
	PULSE_CHECK_HANDLE_RETVAL(device, false);
	PULSE_CHECK_HANDLE_RETVAL(fence, false);

	VulkanDevice* vulkan_device = VULKAN_RETRIEVE_DRIVER_DATA_AS(device, VulkanDevice*);
	if(vulkan_device == PULSE_NULLPTR || vulkan_device->device == VK_NULL_HANDLE)
		return false;
	VkFence vulkan_fence = VULKAN_RETRIEVE_DRIVER_DATA_AS(fence, VkFence);
	if(vulkan_fence == VK_NULL_HANDLE)
		return false;
	VkResult res = vulkan_device->vkGetFenceStatus(vulkan_device->device, vulkan_fence);
	switch(res)
	{
		case VK_SUCCESS:
			if(fence->cmd != PULSE_NULL_HANDLE)
				fence->cmd->state = PULSE_COMMAND_LIST_STATE_READY;
		return true;

		case VK_NOT_READY: return false;
		case VK_ERROR_DEVICE_LOST: PulseSetInternalError(PULSE_ERROR_DEVICE_LOST); return false;

		default: return false;
	}
	return false;
}

bool VulkanWaitForFences(PulseDevice device, const PulseFence* fences, uint32_t fences_count, bool wait_for_all)
{
	if(fences_count == 0)
		return true;
	VulkanDevice* vulkan_device = VULKAN_RETRIEVE_DRIVER_DATA_AS(device, VulkanDevice*);
	if(vulkan_device == PULSE_NULLPTR || vulkan_device->device == VK_NULL_HANDLE)
		return false;
	VkFence* vulkan_fences = (VkFence*)calloc(fences_count, sizeof(VkFence));
	PULSE_CHECK_ALLOCATION_RETVAL(vulkan_fences, false);
	for(uint32_t i = 0; i < fences_count; i++)
	{
		if(fences[i]->cmd == PULSE_NULL_HANDLE && PULSE_IS_BACKEND_LOW_LEVEL_DEBUG(device->backend))
			PulseLogError(device->backend, "cannot wait on a fence that has no command list attached to it");
		vulkan_fences[i] = VULKAN_RETRIEVE_DRIVER_DATA_AS(((PulseFence)fences[i]), VkFence);
	}
	VkResult result = vulkan_device->vkWaitForFences(vulkan_device->device, fences_count, vulkan_fences, wait_for_all, UINT64_MAX);
	free(vulkan_fences);
	switch(result)
	{
		case VK_SUCCESS: break;
		case VK_TIMEOUT: break;

		case VK_ERROR_DEVICE_LOST: PulseSetInternalError(PULSE_ERROR_DEVICE_LOST); return false;
		case VK_ERROR_OUT_OF_HOST_MEMORY: PulseSetInternalError(PULSE_ERROR_CPU_ALLOCATION_FAILED); return false;
		case VK_ERROR_OUT_OF_DEVICE_MEMORY: PulseSetInternalError(PULSE_ERROR_DEVICE_ALLOCATION_FAILED); return false;

		default: break;
	}
	return true;
}
