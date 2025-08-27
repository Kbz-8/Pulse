// Copyright (C) 2025 kanel
// This file is part of "Pulse"
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Pulse.h>

#ifdef PULSE_ENABLE_TEMPLATE_BACKEND

#ifndef PULSE_TEMPLATE_COMPUTE_PIPELINE_H_
#define PULSE_TEMPLATE_COMPUTE_PIPELINE_H_

#include "Template.h"

typedef struct TemplateNameComputePipeline
{
	int dummy;
} TemplateNameComputePipeline;

PulseComputePipeline TemplateNameCreateComputePipeline(PulseDevice device, const PulseComputePipelineCreateInfo* info);
void TemplateNameDestroyComputePipeline(PulseDevice device, PulseComputePipeline pipeline);

#endif // PULSE_TEMPLATE_COMPUTE_PIPELINE_H_

#endif // PULSE_ENABLE_TEMPLATE_BACKEND
