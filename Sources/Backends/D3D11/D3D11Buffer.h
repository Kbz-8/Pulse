// Copyright (C) 2025 kanel
// This file is part of "Pulse"
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Pulse.h>

#ifdef PULSE_ENABLE_D3D11_BACKEND

#ifndef PULSE_D3D11_BUFFER_H_
#define PULSE_D3D11_BUFFER_H_

#include "D3D11.h"

typedef struct Direct3D11Buffer
{
	ID3D11Buffer* buffer;
} Direct3D11Buffer;

PulseBuffer Direct3D11CreateBuffer(PulseDevice device, const PulseBufferCreateInfo* create_infos);
bool Direct3D11MapBuffer(PulseBuffer buffer, PulseMapMode mode, void** data);
void Direct3D11UnmapBuffer(PulseBuffer buffer);
bool Direct3D11CopyBufferToBuffer(PulseCommandList cmd, const PulseBufferRegion* src, const PulseBufferRegion* dst);
bool Direct3D11CopyBufferToImage(PulseCommandList cmd, const PulseBufferRegion* src, const PulseImageRegion* dst);
void Direct3D11DestroyBuffer(PulseDevice device, PulseBuffer buffer);

#endif // PULSE_D3D11_BUFFER_H_

#endif // PULSE_ENABLE_D3D11_BACKEND
