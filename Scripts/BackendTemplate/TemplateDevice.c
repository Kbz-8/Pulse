// Copyright (C) 2025 kbz_8
// This file is part of "Pulse"
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Pulse.h>
#include "../../PulseInternal.h"
#include "Template.h"
#include "TemplateComputePipeline.h"
#include "TemplateCommandList.h"
#include "TemplateDevice.h"
#include "TemplateFence.h"
#include "TemplateBuffer.h"
#include "TemplateImage.h"
#include "TemplateComputePass.h"

PulseDevice TemplateNameCreateDevice(PulseBackend backend, PulseDevice* forbiden_devices, uint32_t forbiden_devices_count)
{
	PULSE_UNUSED(forbiden_devices);
	PULSE_UNUSED(forbiden_devices_count);

	PULSE_CHECK_HANDLE_RETVAL(backend, PULSE_NULLPTR);

	PulseDevice pulse_device = (PulseDeviceHandler*)calloc(1, sizeof(PulseDeviceHandler));
	PULSE_CHECK_ALLOCATION_RETVAL(pulse_device, PULSE_NULL_HANDLE);

	pulse_device->backend = backend;
	PULSE_LOAD_DRIVER_DEVICE(TemplateName);

	if(PULSE_IS_BACKEND_HIGH_LEVEL_DEBUG(backend))
		PulseLogInfoFmt(backend, "(Template) created device from %s", "yes");
	return pulse_device;
}

void TemplateNameDestroyDevice(PulseDevice device)
{
}
