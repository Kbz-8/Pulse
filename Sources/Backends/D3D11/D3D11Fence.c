// Copyright (C) 2025 kanel
// This file is part of "Pulse"
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Pulse.h>
#include "../../PulseInternal.h"
#include "D3D11.h"
#include "D3D11Fence.h"
#include "D3D11CommandList.h"

PulseFence Direct3D11CreateFence(PulseDevice device)
{
	PulseFence fence = (PulseFence)calloc(1, sizeof(PulseFence));
	PULSE_CHECK_ALLOCATION_RETVAL(fence, PULSE_NULL_HANDLE);
	return fence;
}

void Direct3D11DestroyFence(PulseDevice device, PulseFence fence)
{
	free(fence);
}

bool Direct3D11IsFenceReady(PulseDevice device, PulseFence fence)
{
	return true;
}

bool Direct3D11WaitForFences(PulseDevice device, const PulseFence* fences, uint32_t fences_count, bool wait_for_all)
{
	return true;
}
