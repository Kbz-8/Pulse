// Copyright (C) 2025 kbz_8
// This file is part of "Pulse"
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Pulse.h>

#ifdef PULSE_ENABLE_METAL_BACKEND

#ifndef PULSE_METAL_IMAGE_H_
#define PULSE_METAL_IMAGE_H_

#include "Metal.h"

typedef struct MetalImage
{
	int dummy;
} MetalImage;

PulseImage MetalCreateImage(PulseDevice device, const PulseImageCreateInfo* create_infos);
bool MetalIsImageFormatValid(PulseDevice device, PulseImageFormat format, PulseImageType type, PulseImageUsageFlags usage);
bool MetalCopyImageToBuffer(PulseCommandList cmd, const PulseImageRegion* src, const PulseBufferRegion* dst);
bool MetalBlitImage(PulseCommandList cmd, const PulseImageRegion* src, const PulseImageRegion* dst);
void MetalDestroyImage(PulseDevice device, PulseImage image);

#endif // PULSE_METAL_IMAGE_H_

#endif // PULSE_ENABLE_METAL_BACKEND
