// Copyright (C) 2025 kbz_8
// This file is part of "Pulse"
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Pulse.h>

#ifdef PULSE_ENABLE_TEMPLATE_BACKEND

#ifndef PULSE_TEMPLATE_DEVICE_H_
#define PULSE_TEMPLATE_DEVICE_H_

#include "Template.h"

typedef struct TemplateNameDevice
{
	int dummy;
} TemplateNameDevice;

PulseDevice TemplateNameCreateDevice(PulseBackend backend, PulseDevice* forbiden_devices, uint32_t forbiden_devices_count);
void TemplateNameDestroyDevice(PulseDevice device);

#endif // PULSE_TEMPLATE_DEVICE_H_

#endif // PULSE_ENABLE_TEMPLATE_BACKEND
