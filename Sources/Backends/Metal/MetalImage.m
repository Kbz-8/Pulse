// Copyright (C) 2025 kbz_8
// This file is part of "Pulse"
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Pulse.h>
#include "../../PulseInternal.h"
#include "Metal.h"
#include "MetalImage.h"

PulseImage MetalCreateImage(PulseDevice device, const PulseImageCreateInfo* create_infos)
{
}

bool MetalIsImageFormatValid(PulseDevice device, PulseImageFormat format, PulseImageType type, PulseImageUsageFlags usage)
{
}

bool MetalCopyImageToBuffer(PulseCommandList cmd, const PulseImageRegion* src, const PulseBufferRegion* dst)
{
}

bool MetalBlitImage(PulseCommandList cmd, const PulseImageRegion* src, const PulseImageRegion* dst)
{
}

void MetalDestroyImage(PulseDevice device, PulseImage image)
{
}
