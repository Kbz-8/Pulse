// Copyright (C) 2025 kbz_8
// This file is part of "Pulse"
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Pulse.h>

#ifdef PULSE_ENABLE_METAL_BACKEND

#ifndef PULSE_METAL_COMPUTE_PASS_H_
#define PULSE_METAL_COMPUTE_PASS_H_

#include <Metal/Metal.h>
#include "Metal.h"

typedef struct MetalComputePass
{
	id<MTLComputeCommandEncoder> encoder;
} MetalComputePass;

PulseComputePass MetalCreateComputePass(PulseDevice device, PulseCommandList cmd);
void MetalDestroyComputePass(PulseDevice device, PulseComputePass pass);

PulseComputePass MetalBeginComputePass(PulseCommandList cmd);
void MetalEndComputePass(PulseComputePass pass);
void MetalBindStorageBuffers(PulseComputePass pass, const PulseBuffer* buffers, uint32_t num_buffers);
void MetalBindUniformData(PulseComputePass pass, uint32_t slot, const void* data, uint32_t data_size);
void MetalBindStorageImages(PulseComputePass pass, const PulseImage* images, uint32_t num_images);
void MetalBindComputePipeline(PulseComputePass pass, PulseComputePipeline pipeline);
void MetalDispatchComputations(PulseComputePass pass, uint32_t groupcount_x, uint32_t groupcount_y, uint32_t groupcount_z);

#endif // PULSE_METAL_COMPUTE_PASS_H_

#endif // PULSE_ENABLE_METAL_BACKEND
