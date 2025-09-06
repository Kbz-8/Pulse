// Copyright (C) 2025 kanel
// This file is part of "Pulse"
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Pulse.h>
#include "../../PulseInternal.h"
#include "Metal.h"
#include "MetalComputePass.h"
#include "MetalCommandList.h"

PulseComputePass MetalCreateComputePass(PulseDevice device, PulseCommandList cmd)
{
	PULSE_UNUSED(device);
	PulseComputePass pass = (PulseComputePass)calloc(1, sizeof(PulseComputePassHandler));
	PULSE_CHECK_ALLOCATION_RETVAL(pass, PULSE_NULL_HANDLE);
	return pass;
}

void MetalDestroyComputePass(PulseDevice device, PulseComputePass pass)
{
}

PulseComputePass MetalBeginComputePass(PulseCommandList cmd)
{
}

void MetalEndComputePass(PulseComputePass pass)
{
}

void MetalBindStorageBuffers(PulseComputePass pass, const PulseBuffer* buffers, uint32_t num_buffers)
{
}

void MetalBindUniformData(PulseComputePass pass, uint32_t slot, const void* data, uint32_t data_size)
{
}

void MetalBindStorageImages(PulseComputePass pass, const PulseImage* images, uint32_t num_images)
{
}

void MetalBindComputePipeline(PulseComputePass pass, PulseComputePipeline pipeline)
{
}

void MetalDispatchComputations(PulseComputePass pass, uint32_t groupcount_x, uint32_t groupcount_y, uint32_t groupcount_z)
{
}
