// Copyright (C) 2025 kanel
// This file is part of "Pulse"
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Pulse.h>

#ifdef PULSE_ENABLE_D3D11_BACKEND

#ifndef PULSE_D3D11_COMPUTE_PIPELINE_H_
#define PULSE_D3D11_COMPUTE_PIPELINE_H_

#include "D3D11.h"

typedef struct Direct3D11ComputePipeline
{
	int dummy;
} Direct3D11ComputePipeline;

PulseComputePipeline Direct3D11CreateComputePipeline(PulseDevice device, const PulseComputePipelineCreateInfo* info);
void Direct3D11DestroyComputePipeline(PulseDevice device, PulseComputePipeline pipeline);

#endif // PULSE_D3D11_COMPUTE_PIPELINE_H_

#endif // PULSE_ENABLE_D3D11_BACKEND
