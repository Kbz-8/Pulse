// Copyright (C) 2025 kbz_8
// This file is part of "Pulse"
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Pulse.h>
#include "../../PulseInternal.h"
#include "Template.h"
#include "TemplateFence.h"
#include "TemplateDevice.h"
#include "TemplateCommandList.h"
#include "TemplateComputePass.h"
#include "TemplateComputePipeline.h"
#include "TemplateBuffer.h"

PulseCommandList TemplateNameRequestCommandList(PulseDevice device, PulseCommandListUsage usage)
{
	PULSE_CHECK_HANDLE_RETVAL(device, PULSE_NULL_HANDLE);
	PulseCommandList cmd = (PulseCommandList)calloc(1, sizeof(PulseCommandListHandler));
	PULSE_CHECK_ALLOCATION_RETVAL(cmd, PULSE_NULL_HANDLE);
	return cmd;
}

bool TemplateNameSubmitCommandList(PulseDevice device, PulseCommandList cmd, PulseFence fence)
{
}

void TemplateNameReleaseCommandList(PulseDevice device, PulseCommandList cmd)
{
}
