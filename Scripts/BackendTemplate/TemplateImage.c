// Copyright (C) 2025 kanel
// This file is part of "Pulse"
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Pulse.h>
#include "../../PulseInternal.h"
#include "Template.h"
#include "TemplateImage.h"

PulseImage TemplateNameCreateImage(PulseDevice device, const PulseImageCreateInfo* create_infos)
{
}

bool TemplateNameIsImageFormatValid(PulseDevice device, PulseImageFormat format, PulseImageType type, PulseImageUsageFlags usage)
{
}

bool TemplateNameCopyImageToBuffer(PulseCommandList cmd, const PulseImageRegion* src, const PulseBufferRegion* dst)
{
}

bool TemplateNameBlitImage(PulseCommandList cmd, const PulseImageRegion* src, const PulseImageRegion* dst)
{
}

void TemplateNameDestroyImage(PulseDevice device, PulseImage image)
{
}
