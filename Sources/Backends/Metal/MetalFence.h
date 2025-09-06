// Copyright (C) 2025 kanel
// This file is part of "Pulse"
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Pulse.h>

#ifdef PULSE_ENABLE_METAL_BACKEND

#ifndef PULSE_METAL_FENCE_H_
#define PULSE_METAL_FENCE_H_

#include <Pulse.h>
#include "Metal.h"

typedef struct MetalFence
{
	int dummy;
} MetalFence;

PulseFence MetalCreateFence(PulseDevice device);
void MetalDestroyFence(PulseDevice device, PulseFence fence);
bool MetalIsFenceReady(PulseDevice device, PulseFence fence);
bool MetalWaitForFences(PulseDevice device, const PulseFence* fences, uint32_t fences_count, bool wait_for_all);

#endif // PULSE_METAL_FENCE_H_

#endif // PULSE_ENABLE_METAL_BACKEND
