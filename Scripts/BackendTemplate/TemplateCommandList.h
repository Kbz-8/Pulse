// Copyright (C) 2025 kbz_8
// This file is part of "Pulse"
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Pulse.h>

#ifdef PULSE_ENABLE_TEMPLATE_BACKEND

#ifndef PULSE_TEMPLATE_COMMAND_LIST_H_
#define PULSE_TEMPLATE_COMMAND_LIST_H_

#include "Template.h"
#include "TemplateFence.h"

typedef struct TemplateNameCommandList
{
	int dummy;
} TemplateNameCommandList;

PulseCommandList TemplateNameRequestCommandList(PulseDevice device, PulseCommandListUsage usage);
bool TemplateNameSubmitCommandList(PulseDevice device, PulseCommandList cmd, PulseFence fence);
void TemplateNameReleaseCommandList(PulseDevice device, PulseCommandList cmd);

#endif // PULSE_TEMPLATE_COMMAND_LIST_H_

#endif // PULSE_ENABLE_TEMPLATE_BACKEND
