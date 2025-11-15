// Copyright (C) 2025 kbz_8
// This file is part of "Pulse"
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Pulse.h>
#include "../../PulseInternal.h"
#include "D3D11.h"
#include "D3D11Image.h"
#include "D3D11Device.h"

static DXGI_FORMAT PulseImageFormatToDXGIFormat[] = {
    DXGI_FORMAT_UNKNOWN,              // INVALID
    DXGI_FORMAT_A8_UNORM,             // A8_UNORM
    DXGI_FORMAT_R8_UNORM,             // R8_UNORM
    DXGI_FORMAT_R8G8_UNORM,           // R8G8_UNORM
    DXGI_FORMAT_R8G8B8A8_UNORM,       // R8G8B8A8_UNORM
    DXGI_FORMAT_R16_UNORM,            // R16_UNORM
    DXGI_FORMAT_R16G16_UNORM,         // R16G16_UNORM
    DXGI_FORMAT_R16G16B16A16_UNORM,   // R16G16B16A16_UNORM
    DXGI_FORMAT_R10G10B10A2_UNORM,    // R10G10B10A2_UNORM
    DXGI_FORMAT_B5G6R5_UNORM,         // B5G6R5_UNORM
    DXGI_FORMAT_B5G5R5A1_UNORM,       // B5G5R5A1_UNORM
    DXGI_FORMAT_B4G4R4A4_UNORM,       // B4G4R4A4_UNORM
    DXGI_FORMAT_B8G8R8A8_UNORM,       // B8G8R8A8_UNORM
    DXGI_FORMAT_R8_SNORM,             // R8_SNORM
    DXGI_FORMAT_R8G8_SNORM,           // R8G8_SNORM
    DXGI_FORMAT_R8G8B8A8_SNORM,       // R8G8B8A8_SNORM
    DXGI_FORMAT_R16_SNORM,            // R16_SNORM
    DXGI_FORMAT_R16G16_SNORM,         // R16G16_SNORM
    DXGI_FORMAT_R16G16B16A16_SNORM,   // R16G16B16A16_SNORM
    DXGI_FORMAT_R16_FLOAT,            // R16_FLOAT
    DXGI_FORMAT_R16G16_FLOAT,         // R16G16_FLOAT
    DXGI_FORMAT_R16G16B16A16_FLOAT,   // R16G16B16A16_FLOAT
    DXGI_FORMAT_R32_FLOAT,            // R32_FLOAT
    DXGI_FORMAT_R32G32_FLOAT,         // R32G32_FLOAT
    DXGI_FORMAT_R32G32B32A32_FLOAT,   // R32G32B32A32_FLOAT
    DXGI_FORMAT_R11G11B10_FLOAT,      // R11G11B10_UFLOAT
    DXGI_FORMAT_R8_UINT,              // R8_UINT
    DXGI_FORMAT_R8G8_UINT,            // R8G8_UINT
    DXGI_FORMAT_R8G8B8A8_UINT,        // R8G8B8A8_UINT
    DXGI_FORMAT_R16_UINT,             // R16_UINT
    DXGI_FORMAT_R16G16_UINT,          // R16G16_UINT
    DXGI_FORMAT_R16G16B16A16_UINT,    // R16G16B16A16_UINT
    DXGI_FORMAT_R32_UINT,             // R32_UINT
    DXGI_FORMAT_R32G32_UINT,          // R32G32_UINT
    DXGI_FORMAT_R32G32B32A32_UINT,    // R32G32B32A32_UINT
	DXGI_FORMAT_R8_SINT,              // R8_INT
	DXGI_FORMAT_R8G8_SINT,            // R8G8_INT
	DXGI_FORMAT_R8G8B8A8_SINT,        // R8G8B8A8_INT
	DXGI_FORMAT_R16_SINT,             // R16_INT
	DXGI_FORMAT_R16G16_SINT,          // R16G16_INT
	DXGI_FORMAT_R16G16B16A16_SINT,    // R16G16B16A16_INT
	DXGI_FORMAT_R32_SINT,             // R32_INT
	DXGI_FORMAT_R32G32_SINT,          // R32G32_INT
	DXGI_FORMAT_R32G32B32A32_SINT,    // R32G32B32A32_INT
};
PULSE_STATIC_ASSERT(PulseImageFormatToDXGIFormat, PULSE_SIZEOF_ARRAY(PulseImageFormatToDXGIFormat) == PULSE_IMAGE_FORMAT_MAX_ENUM);

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
	Direct3D11Device* d3d11_device = D3D11_RETRIEVE_DRIVER_DATA_AS(device, Direct3D11Device*);
	DXGI_FORMAT dxgi_format = PulseImageFormatToDXGIFormat[format];
	UINT format_support;

	if(FAILED(ID3D11Device_CheckFormatSupport(d3d11_device->device, dxgi_format, &format_support)))
		return false; // Format does not exist ?

	return true;
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
