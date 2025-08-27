// Copyright (C) 2025 kanel
// This file is part of "Pulse"
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Pulse.h>
#include "../../PulseInternal.h"
#include "D3D11.h"
#include "D3D11Device.h"
#include "D3D11ComputePipeline.h"

PulseComputePipeline Direct3D11CreateComputePipeline(PulseDevice device, const PulseComputePipelineCreateInfo* info)
{
	PulseComputePipelineHandler* pipeline = (PulseComputePipelineHandler*)calloc(1, sizeof(PulseComputePipelineHandler));
	PULSE_CHECK_ALLOCATION_RETVAL(pipeline, PULSE_NULL_HANDLE);
	if(PULSE_IS_BACKEND_HIGH_LEVEL_DEBUG(device->backend))
		PulseLogInfoFmt(device->backend, "(D3D11) created new compute pipeline %p", pipeline);
	return pipeline;
}

void Direct3D11DestroyComputePipeline(PulseDevice device, PulseComputePipeline pipeline)
{
}
