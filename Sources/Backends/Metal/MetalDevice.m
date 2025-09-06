// Copyright (C) 2025 kanel
// This file is part of "Pulse"
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Pulse.h>
#include "../../PulseInternal.h"
#include "Metal.h"
#include "MetalComputePipeline.h"
#include "MetalCommandList.h"
#include "MetalDevice.h"
#include "MetalFence.h"
#include "MetalBuffer.h"
#include "MetalImage.h"
#include "MetalComputePass.h"

static uint64_t MetalScoreDevice(id<MTLDevice> device)
{
	uint64_t score = 0;

	if(!device.lowPower)
		score += 1000;

	// A GPU with dedicated memory is typically a dedicated one
	if(!device.hasUnifiedMemory)
		score += 10000;

	score += device.maxThreadsPerThreadgroup.width;
	score += device.maxThreadsPerThreadgroup.height;
	score += device.maxThreadsPerThreadgroup.depth;
	score += device.maxThreadgroupMemoryLength;

	return score;
}

static bool MetalIsDeviceForbidden(id<MTLDevice> device, PulseDevice* forbiden_devices, uint32_t forbiden_devices_count)
{
	if(!device)
		return true;
	for(uint32_t i = 0; i < forbiden_devices_count; i++)
	{
		if(device.registryID == METAL_RETRIEVE_DRIVER_DATA_AS(forbiden_devices[i], MetalDevice*)->device.registryID)
			return true;
	}
	return false;
}

PulseDevice MetalCreateDevice(PulseBackend backend, PulseDevice* forbiden_devices, uint32_t forbiden_devices_count)
{
	@autoreleasepool
	{
		PULSE_UNUSED(forbiden_devices);
		PULSE_UNUSED(forbiden_devices_count);

		PULSE_CHECK_HANDLE_RETVAL(backend, PULSE_NULLPTR);

		PulseDevice pulse_device = (PulseDeviceHandler*)calloc(1, sizeof(PulseDeviceHandler));
		PULSE_CHECK_ALLOCATION_RETVAL(pulse_device, PULSE_NULL_HANDLE);

		MetalDevice* metal_device = (MetalDevice*)calloc(1, sizeof(MetalDevice));
		PULSE_CHECK_ALLOCATION_RETVAL(metal_device, PULSE_NULL_HANDLE);

#ifdef PULSE_PLAT_MACOS
		uint64_t best = 0;
		NSArray<id<MTLDevice>>* devices = MTLCopyAllDevices();
		for(id<MTLDevice> candidate in devices)
		{
			if(MetalIsDeviceForbidden(candidate, forbiden_devices, forbiden_devices_count))
				continue;
			uint64_t current = MetalScoreDevice(candidate);
			if(current > best)
			{
				best = current;
				metal_device->device = candidate;
			}
		}
#endif
		if(!metal_device->device)
		{
			#ifdef PULSE_PLAT_MACOS
				if(PULSE_IS_BACKEND_HIGH_LEVEL_DEBUG(backend))
					PulseLogError(backend, "(Metal) failed to select device, falling back on default device");
			#endif
			id<MTLDevice> device = MTLCreateSystemDefaultDevice();
			if(!MetalIsDeviceForbidden(device, forbiden_devices, forbiden_devices_count))
				metal_device->device = device;
		}

		if(!metal_device->device)
		{
			if(PULSE_IS_BACKEND_LOW_LEVEL_DEBUG(backend))
				PulseLogError(backend, "(Metal) failed to retrieve default device");
			return PULSE_NULL_HANDLE;
		}

		metal_device->queue = [metal_device->device newCommandQueue];

		pulse_device->driver_data = metal_device;
		pulse_device->backend = backend;
		PULSE_LOAD_DRIVER_DEVICE(Metal);

		if(PULSE_IS_BACKEND_HIGH_LEVEL_DEBUG(backend))
			PulseLogInfoFmt(backend, "(Metal) created device from %s", [metal_device->device.name UTF8String]);
		return pulse_device;
	}
}

void MetalDestroyDevice(PulseDevice device)
{
	MetalDevice* metal_device = (MetalDevice*)METAL_RETRIEVE_DRIVER_DATA_AS(device, MetalDevice*);
	if(PULSE_IS_BACKEND_HIGH_LEVEL_DEBUG(device->backend))
		PulseLogInfoFmt(device->backend, "(Metal) destroyed device created from %s", [metal_device->device.name UTF8String]);
	metal_device->queue = nil;
	free(metal_device);
	free(device);
}
