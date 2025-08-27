// Copyright (C) 2025 kanel
// This file is part of "Pulse"
// For conditions of distribution and use, see copyright notice in LICENSE

#include <string.h>

#include <Pulse.h>
#include "../../PulseInternal.h"
#include "Template.h"
#include "TemplateBuffer.h"
#include "TemplateCommandList.h"

PulseBuffer TemplateNameCreateBuffer(PulseDevice device, const PulseBufferCreateInfo* create_infos)
{
	PulseBuffer buffer = (PulseBuffer)calloc(1, sizeof(PulseBufferHandler));
	PULSE_CHECK_ALLOCATION_RETVAL(buffer, PULSE_NULL_HANDLE);
	return buffer;
}

bool TemplateNameMapBuffer(PulseBuffer buffer, PulseMapMode mode, void** data)
{
	return true;
}

void TemplateNameUnmapBuffer(PulseBuffer buffer)
{
}

bool TemplateNameCopyBufferToBuffer(PulseCommandList cmd, const PulseBufferRegion* src, const PulseBufferRegion* dst)
{
	return true;
}

bool TemplateNameCopyBufferToImage(PulseCommandList cmd, const PulseBufferRegion* src, const PulseImageRegion* dst)
{
	return true;
}

void TemplateNameDestroyBuffer(PulseDevice device, PulseBuffer buffer)
{
}
