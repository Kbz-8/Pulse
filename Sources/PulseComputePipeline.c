// Copyright (C) 2025 kanel
// This file is part of "Pulse"
// For conditions of distribution and use, see copyright notice in LICENSE

#include "PulseDefs.h"
#include "PulseInternal.h"

PULSE_API PulseComputePipeline PulseCreateComputePipeline(PulseDevice device, const PulseComputePipelineCreateInfo* info)
{
	PULSE_CHECK_HANDLE_RETVAL(device, PULSE_NULL_HANDLE);
	if(info == PULSE_NULLPTR && PULSE_IS_BACKEND_LOW_LEVEL_DEBUG(device->backend))
		PulseLogError(device->backend, "null infos pointer");
	PULSE_CHECK_PTR_RETVAL(info, PULSE_NULL_HANDLE);
	if(PULSE_IS_BACKEND_LOW_LEVEL_DEBUG(device->backend))
	{
		if(info->code == PULSE_NULLPTR)
			PulseLogError(device->backend, "invalid code pointer passed to PulseComputePipelineCreateInfo");
		if(info->entrypoint == PULSE_NULLPTR)
			PulseLogError(device->backend, "invalid entrypoint pointer passed to PulseComputePipelineCreateInfo");
		if((info->format & device->backend->supported_shader_formats) == 0)
			PulseLogError(device->backend, "invalid shader format passed to PulseComputePipelineCreateInfo");
	}
	PulseComputePipeline pipeline = device->PFN_CreateComputePipeline(device, info);
	if(pipeline == PULSE_NULL_HANDLE)
		return PULSE_NULL_HANDLE;
	pipeline->num_readonly_storage_images = info->num_readonly_storage_images;
	pipeline->num_readonly_storage_buffers = info->num_readonly_storage_buffers;
	pipeline->num_readwrite_storage_images = info->num_readwrite_storage_images;
	pipeline->num_readwrite_storage_buffers = info->num_readwrite_storage_buffers;
	pipeline->num_uniform_buffers = info->num_uniform_buffers;
	return pipeline;
}

PULSE_API void PulseDestroyComputePipeline(PulseDevice device, PulseComputePipeline pipeline)
{
	PULSE_CHECK_HANDLE(device);
	device->PFN_DestroyComputePipeline(device, pipeline);
}
