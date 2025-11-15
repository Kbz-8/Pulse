// Copyright (C) 2025 kbz_8
// This file is part of "Pulse"
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Pulse.h>

#ifdef PULSE_ENABLE_D3D11_BACKEND

#ifndef PULSE_D3D11_FENCE_H_
#define PULSE_D3D11_FENCE_H_

#include <Pulse.h>
#include "D3D11.h"

typedef struct Direct3D11Fence
{
	ID3D11Query* query;
} Direct3D11Fence;

PulseFence Direct3D11CreateFence(PulseDevice device);
void Direct3D11DestroyFence(PulseDevice device, PulseFence fence);
bool Direct3D11IsFenceReady(PulseDevice device, PulseFence fence);
bool Direct3D11WaitForFences(PulseDevice device, const PulseFence* fences, uint32_t fences_count, bool wait_for_all);

#endif // PULSE_D3D11_FENCE_H_

#endif // PULSE_ENABLE_D3D11_BACKEND
