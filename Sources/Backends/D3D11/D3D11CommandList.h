// Copyright (C) 2025 kanel
// This file is part of "Pulse"
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Pulse.h>

#ifdef PULSE_ENABLE_D3D11_BACKEND

#ifndef PULSE_D3D11_COMMAND_LIST_H_
#define PULSE_D3D11_COMMAND_LIST_H_

#include <stdatomic.h>
#include <tinycthread.h>

#include "D3D11.h"
#include "D3D11Fence.h"

typedef struct Direct3D11CommandList
{
	int dummy;
} Direct3D11CommandList;

PulseCommandList Direct3D11RequestCommandList(PulseDevice device, PulseCommandListUsage usage);
bool Direct3D11SubmitCommandList(PulseDevice device, PulseCommandList cmd, PulseFence fence);
void Direct3D11ReleaseCommandList(PulseDevice device, PulseCommandList cmd);

#endif // PULSE_D3D11_COMMAND_LIST_H_

#endif // PULSE_ENABLE_D3D11_BACKEND
