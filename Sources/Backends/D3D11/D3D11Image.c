// Copyright (C) 2025 kanel
// This file is part of "Pulse"
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Pulse.h>
#include "../../PulseInternal.h"
#include "D3D11.h"
#include "D3D11Image.h"

PulseImage Direct3D11CreateImage(PulseDevice device, const PulseImageCreateInfo* create_infos)
{
}

bool Direct3D11IsImageFormatValid(PulseDevice device, PulseImageFormat format, PulseImageType type, PulseImageUsageFlags usage)
{
}

bool Direct3D11CopyImageToBuffer(PulseCommandList cmd, const PulseImageRegion* src, const PulseBufferRegion* dst)
{
}

bool Direct3D11BlitImage(PulseCommandList cmd, const PulseImageRegion* src, const PulseImageRegion* dst)
{
}

void Direct3D11DestroyImage(PulseDevice device, PulseImage image)
{
}
