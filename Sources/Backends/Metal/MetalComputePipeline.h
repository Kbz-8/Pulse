// Copyright (C) 2025 kbz_8
// This file is part of "Pulse"
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Pulse.h>

#ifdef PULSE_ENABLE_METAL_BACKEND

#ifndef PULSE_METAL_COMPUTE_PIPELINE_H_
#define PULSE_METAL_COMPUTE_PIPELINE_H_

#include <Metal/Metal.h>
#include "Metal.h"

typedef struct MetalComputePipeline
{
	id<MTLComputePipelineState> pipeline;
} MetalComputePipeline;

PulseComputePipeline MetalCreateComputePipeline(PulseDevice device, const PulseComputePipelineCreateInfo* info);
void MetalDestroyComputePipeline(PulseDevice device, PulseComputePipeline pipeline);

#endif // PULSE_METAL_COMPUTE_PIPELINE_H_

#endif // PULSE_ENABLE_METAL_BACKEND
