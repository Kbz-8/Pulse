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
	if(create_infos->usage & (PULSE_BUFFER_USAGE_TRANSFER_UPLOAD))
		description.CPUAccessFlags |= D3D11_CPU_ACCESS_WRITE;
	if(create_infos->usage & (PULSE_BUFFER_USAGE_TRANSFER_DOWNLOAD))
		description.CPUAccessFlags |= D3D11_CPU_ACCESS_READ;

	CHECK_D3D11_RETVAL(device->backend, ID3D11Device_CreateBuffer(d3d11_device->device, &description, PULSE_NULLPTR, &d3d11_buffer->buffer), PULSE_ERROR_INITIALIZATION_FAILED, PULSE_NULL_HANDLE);

	if(create_infos->usage & (PULSE_BUFFER_USAGE_STORAGE_READ | PULSE_BUFFER_USAGE_STORAGE_WRITE))
	{
		D3D11_UNORDERED_ACCESS_VIEW_DESC unordered_access_view_description;
		unordered_access_view_description.Format = DXGI_FORMAT_R32_TYPELESS;
		unordered_access_view_description.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
		unordered_access_view_description.Buffer.FirstElement = 0;
		unordered_access_view_description.Buffer.NumElements = create_infos->size / sizeof(uint32_t);
		unordered_access_view_description.Buffer.Flags = D3D11_BUFFER_UAV_FLAG_RAW;
		CHECK_D3D11_RETVAL(device->backend, ID3D11Device_CreateUnorderedAccessView(d3d11_device->device, (ID3D11Resource*)d3d11_buffer->buffer, &unordered_access_view_description, &d3d11_buffer->unordered_access_view), PULSE_ERROR_INITIALIZATION_FAILED, PULSE_NULL_HANDLE);

		D3D11_SHADER_RESOURCE_VIEW_DESC shader_resource_view_description;
		shader_resource_view_description.Format = DXGI_FORMAT_R32_TYPELESS;
		shader_resource_view_description.ViewDimension = D3D11_SRV_DIMENSION_BUFFEREX;
		shader_resource_view_description.BufferEx.FirstElement = 0;
		shader_resource_view_description.BufferEx.NumElements = create_infos->size / sizeof(uint32_t);
		shader_resource_view_description.BufferEx.Flags = D3D11_BUFFEREX_SRV_FLAG_RAW;
		CHECK_D3D11_RETVAL(device->backend, ID3D11Device_CreateShaderResourceView(d3d11_device->device, (ID3D11Resource*)d3d11_buffer->buffer, &shader_resource_view_description, &d3d11_buffer->shader_resource_view), PULSE_ERROR_INITIALIZATION_FAILED, PULSE_NULL_HANDLE);
	}

	return buffer;
}

bool Direct3D11MapBuffer(PulseBuffer buffer, PulseMapMode mode, void** data)
{
	Direct3D11Device* d3d11_device = D3D11_RETRIEVE_DRIVER_DATA_AS(buffer->device, Direct3D11Device*);
	Direct3D11Buffer* d3d11_buffer = D3D11_RETRIEVE_DRIVER_DATA_AS(buffer, Direct3D11Buffer*);

	D3D11_MAPPED_SUBRESOURCE subresource;
	CHECK_D3D11_RETVAL(buffer->device->backend, ID3D11DeviceContext_Map(d3d11_device->context, (ID3D11Resource*)d3d11_buffer->buffer, 0, (mode == PULSE_MAP_READ) ? D3D11_MAP_READ : D3D11_MAP_WRITE, 0, &subresource), PULSE_ERROR_MAP_FAILED, false);
	*data = subresource.pData;
	return true;
}

void Direct3D11UnmapBuffer(PulseBuffer buffer)
{
	Direct3D11Device* d3d11_device = D3D11_RETRIEVE_DRIVER_DATA_AS(buffer->device, Direct3D11Device*);
	Direct3D11Buffer* d3d11_buffer = D3D11_RETRIEVE_DRIVER_DATA_AS(buffer, Direct3D11Buffer*);
	ID3D11DeviceContext_Unmap(d3d11_device->context, (ID3D11Resource*)d3d11_buffer->buffer, 0);
}

bool Direct3D11CopyBufferToBuffer(PulseCommandList cmd, const PulseBufferRegion* src, const PulseBufferRegion* dst)
{
	Direct3D11Buffer* d3d11_src_buffer = D3D11_RETRIEVE_DRIVER_DATA_AS(src->buffer, Direct3D11Buffer*);
	Direct3D11Buffer* d3d11_dst_buffer = D3D11_RETRIEVE_DRIVER_DATA_AS(dst->buffer, Direct3D11Buffer*);
	Direct3D11CommandList* d3d11_cmd = D3D11_RETRIEVE_DRIVER_DATA_AS(cmd, Direct3D11CommandList*);

	D3D11_BOX src_box = { src->offset, 0, 0, src->offset + src->size, 1, 1 };

	ID3D11DeviceContext_CopySubresourceRegion(
		d3d11_cmd->context,
		(ID3D11Resource*)d3d11_dst_buffer->buffer,
		0,
		dst->offset,
		0,
		0,
		(ID3D11Resource*)d3d11_src_buffer->buffer,
		0,
		&src_box
	);
	return true;
}

bool Direct3D11CopyBufferToImage(PulseCommandList cmd, const PulseBufferRegion* src, const PulseImageRegion* dst)
{
	return true;
}

void Direct3D11DestroyBuffer(PulseDevice device, PulseBuffer buffer)
{
	Direct3D11Buffer* d3d11_buffer = D3D11_RETRIEVE_DRIVER_DATA_AS(buffer, Direct3D11Buffer*);
	if(d3d11_buffer->unordered_access_view)
		ID3D11UnorderedAccessView_Release(d3d11_buffer->unordered_access_view);
	if(d3d11_buffer->shader_resource_view)
		ID3D11ShaderResourceView_Release(d3d11_buffer->shader_resource_view);
	ID3D11Buffer_Release(d3d11_buffer->buffer);
	free(d3d11_buffer);
	free(buffer);
}
