// Copyright (C) 2025 kanel
// This file is part of "Pulse"
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Pulse.h>
#include "../../PulseInternal.h"
#include "D3D11.h"
#include "D3D11ComputePass.h"
#include "D3D11CommandList.h"

PulseComputePass Direct3D11CreateComputePass(PulseDevice device, PulseCommandList cmd)
{
	PULSE_UNUSED(device);
	PulseComputePass pass = (PulseComputePass)calloc(1, sizeof(PulseComputePassHandler));
	PULSE_CHECK_ALLOCATION_RETVAL(pass, PULSE_NULL_HANDLE);
	return pass;
}

void Direct3D11DestroyComputePass(PulseDevice device, PulseComputePass pass)
{
}

PulseComputePass Direct3D11BeginComputePass(PulseCommandList cmd)
{
}

void Direct3D11EndComputePass(PulseComputePass pass)
{
}

void Direct3D11BindStorageBuffers(PulseComputePass pass, const PulseBuffer* buffers, uint32_t num_buffers)
{
}

void Direct3D11BindUniformData(PulseComputePass pass, uint32_t slot, const void* data, uint32_t data_size)
{
}

void Direct3D11BindStorageImages(PulseComputePass pass, const PulseImage* images, uint32_t num_images)
{
}

void Direct3D11BindComputePipeline(PulseComputePass pass, PulseComputePipeline pipeline)
{
}

void Direct3D11DispatchComputations(PulseComputePass pass, uint32_t groupcount_x, uint32_t groupcount_y, uint32_t groupcount_z)
{
}
