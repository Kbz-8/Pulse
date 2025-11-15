// Copyright (C) 2025 kbz_8
// This file is part of "Pulse"
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Pulse.h>
#include "../../PulseInternal.h"
#include "Template.h"
#include "TemplateFence.h"
#include "TemplateCommandList.h"

PulseFence TemplateNameCreateFence(PulseDevice device)
{
	PulseFence fence = (PulseFence)calloc(1, sizeof(PulseFence));
	PULSE_CHECK_ALLOCATION_RETVAL(fence, PULSE_NULL_HANDLE);
	return fence;
}

void TemplateNameDestroyFence(PulseDevice device, PulseFence fence)
{
	free(fence);
}

bool TemplateNameIsFenceReady(PulseDevice device, PulseFence fence)
{
	return true;
}

bool TemplateNameWaitForFences(PulseDevice device, const PulseFence* fences, uint32_t fences_count, bool wait_for_all)
{
	return true;
}
