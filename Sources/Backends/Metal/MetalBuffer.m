// Copyright (C) 2025 kanel
// This file is part of "Pulse"
// For conditions of distribution and use, see copyright notice in LICENSE

#include <string.h>

#include <Pulse.h>
#include "../../PulseInternal.h"
#include "Metal.h"
#include "MetalBuffer.h"
#include "MetalDevice.h"
#include "MetalCommandList.h"

PulseBuffer MetalCreateBuffer(PulseDevice device, const PulseBufferCreateInfo* create_infos)
{
	@autoreleasepool
	{
		MetalDevice* metal_device = (MetalDevice*)METAL_RETRIEVE_DRIVER_DATA_AS(device, MetalDevice*);

		PulseBuffer buffer = (PulseBuffer)calloc(1, sizeof(PulseBufferHandler));
		PULSE_CHECK_ALLOCATION_RETVAL(buffer, PULSE_NULL_HANDLE);

		MetalBuffer* metal_buffer = (MetalBuffer*)calloc(1, sizeof(MetalBuffer));
		PULSE_CHECK_ALLOCATION_RETVAL(metal_buffer, PULSE_NULL_HANDLE);

		uint32_t size = PULSE_ALIGN_UP(create_infos->size, 4);

		buffer->device = device;
		buffer->driver_data = metal_buffer;
		buffer->size = size;
		buffer->usage = create_infos->usage;

		MTLResourceOptions options;
		if((create_infos->usage & (PULSE_BUFFER_USAGE_TRANSFER_UPLOAD | PULSE_BUFFER_USAGE_TRANSFER_DOWNLOAD)) == 0) // Is storage only
			options = MTLResourceStorageModePrivate;
		else if((create_infos->usage & PULSE_BUFFER_USAGE_TRANSFER_DOWNLOAD) == 0)
			options = MTLResourceCPUCacheModeWriteCombined;
		else
			options = MTLResourceCPUCacheModeDefaultCache;

		metal_buffer->buffer = [metal_device->device newBufferWithLength:size options:options];
		CHECK_METAL_RETVAL(device->backend, metal_buffer->buffer, PULSE_ERROR_INITIALIZATION_FAILED, PULSE_NULL_HANDLE);

		return buffer;
	}
}

bool MetalMapBuffer(PulseBuffer buffer, PulseMapMode mode, void** data)
{
	return true;
}

void MetalUnmapBuffer(PulseBuffer buffer)
{
}

bool MetalCopyBufferToBuffer(PulseCommandList cmd, const PulseBufferRegion* src, const PulseBufferRegion* dst)
{
	return true;
}

bool MetalCopyBufferToImage(PulseCommandList cmd, const PulseBufferRegion* src, const PulseImageRegion* dst)
{
	return true;
}

void MetalDestroyBuffer(PulseDevice device, PulseBuffer buffer)
{
	MetalBuffer* metal_buffer = METAL_RETRIEVE_DRIVER_DATA_AS(buffer, MetalBuffer*);
	metal_buffer->buffer = nil;
	free(metal_buffer);
	free(buffer);
}
