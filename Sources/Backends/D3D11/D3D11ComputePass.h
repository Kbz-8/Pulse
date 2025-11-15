// Copyright (C) 2025 kbz_8
// This file is part of "Pulse"
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Pulse.h>

#ifdef PULSE_ENABLE_D3D11_BACKEND

#ifndef PULSE_D3D11_COMPUTE_PASS_H_
#define PULSE_D3D11_COMPUTE_PASS_H_

#include "D3D11.h"

typedef struct Direct3D11ComputePass
{
	bool should_bind_read_only_resources;
	bool should_bind_write_resources;
	bool should_bind_uniform_resources;
} Direct3D11ComputePass;

PulseComputePass Direct3D11CreateComputePass(PulseDevice device, PulseCommandList cmd);
void Direct3D11DestroyComputePass(PulseDevice device, PulseComputePass pass);

PulseComputePass Direct3D11BeginComputePass(PulseCommandList cmd);
void Direct3D11EndComputePass(PulseComputePass pass);
void Direct3D11BindStorageBuffers(PulseComputePass pass, const PulseBuffer* buffers, uint32_t num_buffers);
void Direct3D11BindUniformData(PulseComputePass pass, uint32_t slot, const void* data, uint32_t data_size);
void Direct3D11BindStorageImages(PulseComputePass pass, const PulseImage* images, uint32_t num_images);
void Direct3D11BindComputePipeline(PulseComputePass pass, PulseComputePipeline pipeline);
void Direct3D11DispatchComputations(PulseComputePass pass, uint32_t groupcount_x, uint32_t groupcount_y, uint32_t groupcount_z);

#endif // PULSE_D3D11_COMPUTE_PASS_H_

#endif // PULSE_ENABLE_D3D11_BACKEND
