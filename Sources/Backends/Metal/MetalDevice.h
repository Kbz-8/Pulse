// Copyright (C) 2025 kanel
// This file is part of "Pulse"
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Pulse.h>

#ifdef PULSE_ENABLE_METAL_BACKEND

#ifndef PULSE_METAL_DEVICE_H_
#define PULSE_METAL_DEVICE_H_

#include <Metal/Metal.h>
#include "Metal.h"

typedef struct MetalDevice
{
	id<MTLDevice> device;
	id<MTLCommandQueue> queue;
} MetalDevice;

PulseDevice MetalCreateDevice(PulseBackend backend, PulseDevice* forbiden_devices, uint32_t forbiden_devices_count);
void MetalDestroyDevice(PulseDevice device);

#endif // PULSE_METAL_DEVICE_H_

#endif // PULSE_ENABLE_METAL_BACKEND
