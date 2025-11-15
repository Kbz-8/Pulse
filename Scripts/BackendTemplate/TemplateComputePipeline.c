// Copyright (C) 2025 kbz_8
// This file is part of "Pulse"
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Pulse.h>
#include "../../PulseInternal.h"
#include "Template.h"
#include "TemplateDevice.h"
#include "TemplateComputePipeline.h"

PulseComputePipeline TemplateNameCreateComputePipeline(PulseDevice device, const PulseComputePipelineCreateInfo* info)
{
	PulseComputePipelineHandler* pipeline = (PulseComputePipelineHandler*)calloc(1, sizeof(PulseComputePipelineHandler));
	PULSE_CHECK_ALLOCATION_RETVAL(pipeline, PULSE_NULL_HANDLE);
	if(PULSE_IS_BACKEND_HIGH_LEVEL_DEBUG(device->backend))
		PulseLogInfoFmt(device->backend, "(Template) created new compute pipeline %p", pipeline);
	return pipeline;
}

void TemplateNameDestroyComputePipeline(PulseDevice device, PulseComputePipeline pipeline)
{
}
