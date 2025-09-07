// Copyright (C) 2025 kanel
// This file is part of "Pulse"
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Pulse.h>

#ifdef PULSE_ENABLE_METAL_BACKEND

#ifndef PULSE_METAL_COMMAND_LIST_H_
#define PULSE_METAL_COMMAND_LIST_H_

#include <Metal/Metal.h>
#include "Metal.h"
#include "MetalFence.h"

typedef struct MetalCommandList
{
	id<MTLCommandBuffer> cmd;
	id<MTLBlitCommandEncoder> copy_encoder;
} MetalCommandList;

PulseCommandList MetalRequestCommandList(PulseDevice device, PulseCommandListUsage usage);
bool MetalSubmitCommandList(PulseDevice device, PulseCommandList cmd, PulseFence fence);
void MetalReleaseCommandList(PulseDevice device, PulseCommandList cmd);

#endif // PULSE_METAL_COMMAND_LIST_H_

#endif // PULSE_ENABLE_METAL_BACKEND
