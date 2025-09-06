// Copyright (C) 2025 kanel
// This file is part of "Pulse"
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Pulse.h>

#ifdef PULSE_ENABLE_METAL_BACKEND

#ifndef PULSE_METAL_BUFFER_H_
#define PULSE_METAL_BUFFER_H_

#include <Metal/Metal.h>
#include "Metal.h"

typedef struct MetalBuffer
{
	id<MTLBuffer> buffer;
} MetalBuffer;

PulseBuffer MetalCreateBuffer(PulseDevice device, const PulseBufferCreateInfo* create_infos);
bool MetalMapBuffer(PulseBuffer buffer, PulseMapMode mode, void** data);
void MetalUnmapBuffer(PulseBuffer buffer);
bool MetalCopyBufferToBuffer(PulseCommandList cmd, const PulseBufferRegion* src, const PulseBufferRegion* dst);
bool MetalCopyBufferToImage(PulseCommandList cmd, const PulseBufferRegion* src, const PulseImageRegion* dst);
void MetalDestroyBuffer(PulseDevice device, PulseBuffer buffer);

#endif // PULSE_METAL_BUFFER_H_

#endif // PULSE_ENABLE_METAL_BACKEND
