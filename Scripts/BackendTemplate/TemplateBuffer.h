// Copyright (C) 2025 kbz_8
// This file is part of "Pulse"
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Pulse.h>

#ifdef PULSE_ENABLE_TEMPLATE_BACKEND

#ifndef PULSE_TEMPLATE_BUFFER_H_
#define PULSE_TEMPLATE_BUFFER_H_

#include "Template.h"

typedef struct TemplateNameBuffer
{
	int dummy;
} TemplateNameBuffer;

PulseBuffer TemplateNameCreateBuffer(PulseDevice device, const PulseBufferCreateInfo* create_infos);
bool TemplateNameMapBuffer(PulseBuffer buffer, PulseMapMode mode, void** data);
void TemplateNameUnmapBuffer(PulseBuffer buffer);
bool TemplateNameCopyBufferToBuffer(PulseCommandList cmd, const PulseBufferRegion* src, const PulseBufferRegion* dst);
bool TemplateNameCopyBufferToImage(PulseCommandList cmd, const PulseBufferRegion* src, const PulseImageRegion* dst);
void TemplateNameDestroyBuffer(PulseDevice device, PulseBuffer buffer);

#endif // PULSE_TEMPLATE_BUFFER_H_

#endif // PULSE_ENABLE_TEMPLATE_BACKEND
