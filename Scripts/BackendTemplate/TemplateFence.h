// Copyright (C) 2025 kanel
// This file is part of "Pulse"
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Pulse.h>

#ifdef PULSE_ENABLE_TEMPLATE_BACKEND

#ifndef PULSE_TEMPLATE_FENCE_H_
#define PULSE_TEMPLATE_FENCE_H_

#include <Pulse.h>
#include "Template.h"

typedef struct TemplateNameFence
{
	int dummy;
} TemplateNameFence;

PulseFence TemplateNameCreateFence(PulseDevice device);
void TemplateNameDestroyFence(PulseDevice device, PulseFence fence);
bool TemplateNameIsFenceReady(PulseDevice device, PulseFence fence);
bool TemplateNameWaitForFences(PulseDevice device, const PulseFence* fences, uint32_t fences_count, bool wait_for_all);

#endif // PULSE_TEMPLATE_FENCE_H_

#endif // PULSE_ENABLE_TEMPLATE_BACKEND
