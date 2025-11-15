// Copyright (C) 2025 kbz_8
// This file is part of "Pulse"
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Pulse.h>

#ifdef PULSE_ENABLE_TEMPLATE_BACKEND

#ifndef PULSE_TEMPLATE_IMAGE_H_
#define PULSE_TEMPLATE_IMAGE_H_

#include "Template.h"

typedef struct TemplateNameImage
{
	int dummy;
} TemplateNameImage;

PulseImage TemplateNameCreateImage(PulseDevice device, const PulseImageCreateInfo* create_infos);
bool TemplateNameIsImageFormatValid(PulseDevice device, PulseImageFormat format, PulseImageType type, PulseImageUsageFlags usage);
bool TemplateNameCopyImageToBuffer(PulseCommandList cmd, const PulseImageRegion* src, const PulseBufferRegion* dst);
bool TemplateNameBlitImage(PulseCommandList cmd, const PulseImageRegion* src, const PulseImageRegion* dst);
void TemplateNameDestroyImage(PulseDevice device, PulseImage image);

#endif // PULSE_TEMPLATE_IMAGE_H_

#endif // PULSE_ENABLE_TEMPLATE_BACKEND
