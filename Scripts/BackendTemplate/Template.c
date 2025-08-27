// Copyright (C) 2025 kanel
// This file is part of "Pulse"
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Pulse.h>
#include "../../PulseInternal.h"

#include "Template.h"
#include "TemplateDevice.h"

PulseBackendFlags TemplateNameCheckSupport(PulseBackendFlags candidates, PulseShaderFormatsFlags shader_formats_used)
{
	if(candidates != PULSE_BACKEND_ANY && (candidates & PULSE_BACKEND_TEMPLATE) == 0)
		return PULSE_BACKEND_INVALID;
	//if((shader_formats_used & PULSE_SHADER_FORMAT_SPIRV_BIT) == 0)
	//	return PULSE_BACKEND_INVALID;
	return PULSE_BACKEND_TEMPLATE;
}

bool TemplateNameLoadBackend(PulseBackend backend, PulseDebugLevel debug_level)
{
	PULSE_UNUSED(backend);
	PULSE_UNUSED(debug_level);
	return true;
}

void TemplateNameUnloadBackend(PulseBackend backend)
{
}

PulseBackendHandler TemplateNameDriver = {
	.PFN_LoadBackend = TemplateNameLoadBackend,
	.PFN_UnloadBackend = TemplateNameUnloadBackend,
	.PFN_CreateDevice = TemplateNameCreateDevice,
	.backend = PULSE_BACKEND_TEMPLATE,
	.supported_shader_formats = PULSE_SHADER_FORMAT_SPIRV_BIT,
	.driver_data = PULSE_NULLPTR
};
