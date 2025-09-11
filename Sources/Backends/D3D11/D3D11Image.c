// Copyright (C) 2025 kanel
// This file is part of "Pulse"
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Pulse.h>
#include "../../PulseInternal.h"
#include "D3D11.h"
#include "D3D11Image.h"
#include "D3D11Device.h"

PulseImage Direct3D11CreateImage(PulseDevice device, const PulseImageCreateInfo* create_infos)
{
	Direct3D11Device* d3d11_device = D3D11_RETRIEVE_DRIVER_DATA_AS(device, Direct3D11Device*);

	PulseImage image = (PulseImage)calloc(1, sizeof(PulseImageHandler));
	PULSE_CHECK_ALLOCATION_RETVAL(image, PULSE_NULL_HANDLE);

	Direct3D11Image* d3d11_image = (Direct3D11Image*)calloc(1, sizeof(Direct3D11Image));
	PULSE_CHECK_ALLOCATION_RETVAL(d3d11_image, PULSE_NULL_HANDLE);

	return image;
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
	Direct3D11Image* d3d11_image = D3D11_RETRIEVE_DRIVER_DATA_AS(image, Direct3D11Image*);
	free(d3d11_image);
	free(image);
}
