// Copyright (C) 2025 kanel
// This file is part of "Pulse"
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Pulse.h>
#include <stdlib.h>
#include "../../PulseInternal.h"
#include "D3D11.h"
#include "D3D11Device.h"
#include "D3D11Buffer.h"
#include "D3D11CommandList.h"

PulseBuffer Direct3D11CreateBuffer(PulseDevice device, const PulseBufferCreateInfo* create_infos)
{
	Direct3D11Device* d3d11_device = D3D11_RETRIEVE_DRIVER_DATA_AS(device, Direct3D11Device*);

	PulseBuffer buffer = (PulseBuffer)calloc(1, sizeof(PulseBufferHandler));
	PULSE_CHECK_ALLOCATION_RETVAL(buffer, PULSE_NULL_HANDLE);

	Direct3D11Buffer* d3d11_buffer = (Direct3D11Buffer*)calloc(1, sizeof(Direct3D11Buffer));
	PULSE_CHECK_ALLOCATION_RETVAL(d3d11_buffer, PULSE_NULL_HANDLE);

	buffer->device = device;
	buffer->driver_data = d3d11_buffer;
	buffer->size = create_infos->size;
	buffer->usage = create_infos->usage;

	D3D11_BUFFER_DESC description = { 0 };
	description.ByteWidth = create_infos->size;
	description.Usage = D3D11_USAGE_DEFAULT;
	if(create_infos->usage & (PULSE_BUFFER_USAGE_STORAGE_READ | PULSE_BUFFER_USAGE_STORAGE_WRITE))
	{
		description.BindFlags |= D3D11_BIND_UNORDERED_ACCESS | D3D11_BIND_SHADER_RESOURCE;
		description.MiscFlags |= D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS;
	}

	CHECK_D3D11_RETVAL(device->backend, ID3D11Device_CreateBuffer(d3d11_device->device, &description, PULSE_NULLPTR, &d3d11_buffer->buffer), PULSE_ERROR_INITIALIZATION_FAILED, PULSE_NULL_HANDLE);

	return buffer;
}

bool Direct3D11MapBuffer(PulseBuffer buffer, PulseMapMode mode, void** data)
{
	return true;
}

void Direct3D11UnmapBuffer(PulseBuffer buffer)
{
}

bool Direct3D11CopyBufferToBuffer(PulseCommandList cmd, const PulseBufferRegion* src, const PulseBufferRegion* dst)
{
	return true;
}

bool Direct3D11CopyBufferToImage(PulseCommandList cmd, const PulseBufferRegion* src, const PulseImageRegion* dst)
{
	return true;
}

void Direct3D11DestroyBuffer(PulseDevice device, PulseBuffer buffer)
{
	Direct3D11Buffer* d3d11_buffer = D3D11_RETRIEVE_DRIVER_DATA_AS(buffer, Direct3D11Buffer*);
	ID3D11Buffer_Release(d3d11_buffer->buffer);
	free(d3d11_buffer);
	free(buffer);
}
