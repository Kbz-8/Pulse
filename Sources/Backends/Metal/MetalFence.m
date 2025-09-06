// Copyright (C) 2025 kanel
// This file is part of "Pulse"
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Pulse.h>
#include "../../PulseInternal.h"
#include "Metal.h"
#include "MetalFence.h"
#include "MetalCommandList.h"

PulseFence MetalCreateFence(PulseDevice device)
{
	PulseFence fence = (PulseFence)calloc(1, sizeof(PulseFence));
	PULSE_CHECK_ALLOCATION_RETVAL(fence, PULSE_NULL_HANDLE);
	return fence;
}

void MetalDestroyFence(PulseDevice device, PulseFence fence)
{
	free(fence);
}

bool MetalIsFenceReady(PulseDevice device, PulseFence fence)
{
	return true;
}

bool MetalWaitForFences(PulseDevice device, const PulseFence* fences, uint32_t fences_count, bool wait_for_all)
{
	return true;
}
