// Copyright (C) 2025 kanel
// This file is part of "Pulse"
// For conditions of distribution and use, see copyright notice in LICENSE

#include <string.h>

#include <Pulse.h>
#include "../../PulseInternal.h"
#include "D3D11.h"
#include "D3D11Buffer.h"
#include "D3D11CommandList.h"

PulseBuffer Direct3D11CreateBuffer(PulseDevice device, const PulseBufferCreateInfo* create_infos)
{
	PulseBuffer buffer = (PulseBuffer)calloc(1, sizeof(PulseBufferHandler));
	PULSE_CHECK_ALLOCATION_RETVAL(buffer, PULSE_NULL_HANDLE);
	return buffer;
}

bool Direct3D11MapBuffer(PulseBuffer buffer, PulseMapMode mode, void** data)
{
	return true;
}

void Direct3D11UnmapBuffer(PulseBuffer buffer)
{
}

bool Direct3D11CopyBufferToBuffer(PulseCommandList cmd, const PulseBufferRegion* src, const PulseBufferRegion* dst)
{
	return true;
}

bool Direct3D11CopyBufferToImage(PulseCommandList cmd, const PulseBufferRegion* src, const PulseImageRegion* dst)
{
	return true;
}

void Direct3D11DestroyBuffer(PulseDevice device, PulseBuffer buffer)
{
}
