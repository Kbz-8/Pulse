// Copyright (C) 2025 kbz_8
// This file is part of "Pulse"
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Pulse.h>
#include "../../PulseInternal.h"
#include "D3D11.h"
#include "D3D11Buffer.h"
#include "D3D11ComputePass.h"
#include "D3D11CommandList.h"
#include "D3D11ComputePipeline.h"

static void Direct3D11BindResources(PulseComputePass pass)
{
	Direct3D11ComputePass* d3d11_pass = D3D11_RETRIEVE_DRIVER_DATA_AS(pass, Direct3D11ComputePass*);
	Direct3D11CommandList* d3d11_cmd = D3D11_RETRIEVE_DRIVER_DATA_AS(pass->cmd, Direct3D11CommandList*);
	Direct3D11ComputePipeline* d3d11_pipeline = D3D11_RETRIEVE_DRIVER_DATA_AS(pass->current_pipeline, Direct3D11ComputePipeline*);

	if(d3d11_pass->should_bind_read_only_resources)
	{
		uint32_t entry_index = 0;
		for(uint32_t i = 0; i < pass->current_pipeline->num_readonly_storage_images; i++, entry_index++)
		{
		}

		ID3D11ShaderResourceView* buffer_resource_views[PULSE_MAX_READ_BUFFERS_BOUND];
		for(uint32_t i = 0; i < pass->current_pipeline->num_readonly_storage_buffers; i++, entry_index++)
		{
			Direct3D11Buffer* d3d11_buffer = D3D11_RETRIEVE_DRIVER_DATA_AS(pass->readonly_storage_buffers[i], Direct3D11Buffer*);
			buffer_resource_views[i] = d3d11_buffer->shader_resource_view;
		}
		ID3D11DeviceContext_CSSetShaderResources(d3d11_cmd->context, pass->current_pipeline->num_readonly_storage_images, pass->current_pipeline->num_readonly_storage_buffers, buffer_resource_views);

		d3d11_pass->should_bind_read_only_resources = false;
	}
	if(d3d11_pass->should_bind_write_resources)
	{
		ID3D11UnorderedAccessView* resource_views[PULSE_MAX_WRITE_TEXTURES_BOUND + PULSE_MAX_WRITE_BUFFERS_BOUND];
		uint32_t entry_index = 0;
		for(uint32_t i = 0; i < pass->current_pipeline->num_readwrite_storage_images; i++, entry_index++)
		{
		}

		for(uint32_t i = 0; i < pass->current_pipeline->num_readwrite_storage_buffers; i++, entry_index++)
		{
			Direct3D11Buffer* d3d11_buffer = D3D11_RETRIEVE_DRIVER_DATA_AS(pass->readwrite_storage_buffers[i], Direct3D11Buffer*);
			resource_views[entry_index] = d3d11_buffer->unordered_access_view;
		}
		ID3D11DeviceContext_CSSetUnorderedAccessViews(d3d11_cmd->context, 0, pass->current_pipeline->num_readwrite_storage_images + pass->current_pipeline->num_readwrite_storage_buffers, resource_views, PULSE_NULLPTR);

		d3d11_pass->should_bind_write_resources = false;
	}
}

PulseComputePass Direct3D11CreateComputePass(PulseDevice device, PulseCommandList cmd)
{
	PULSE_UNUSED(device);
	PulseComputePass pass = (PulseComputePass)calloc(1, sizeof(PulseComputePassHandler));
	PULSE_CHECK_ALLOCATION_RETVAL(pass, PULSE_NULL_HANDLE);
	Direct3D11ComputePass* d3d11_pass = (Direct3D11ComputePass*)calloc(1, sizeof(Direct3D11ComputePass));
	PULSE_CHECK_ALLOCATION_RETVAL(d3d11_pass, PULSE_NULL_HANDLE);

	pass->cmd = cmd;
	pass->driver_data = d3d11_pass;

	return pass;
}

void Direct3D11DestroyComputePass(PulseDevice device, PulseComputePass pass)
{
	PULSE_UNUSED(device);
	Direct3D11ComputePass* d3d11_pass = D3D11_RETRIEVE_DRIVER_DATA_AS(pass, Direct3D11ComputePass*);
	free(d3d11_pass);
	free(pass);
}

PulseComputePass Direct3D11BeginComputePass(PulseCommandList cmd)
{
	return cmd->pass;
}

void Direct3D11EndComputePass(PulseComputePass pass)
{
}

void Direct3D11BindStorageBuffers(PulseComputePass pass, const PulseBuffer* buffers, uint32_t num_buffers)
{
	PulseBufferUsageFlags usage = buffers[0]->usage;
	bool is_readwrite = (usage & PULSE_BUFFER_USAGE_STORAGE_WRITE) != 0;
	PulseBuffer* array = is_readwrite ? pass->readwrite_storage_buffers : pass->readonly_storage_buffers;
	Direct3D11ComputePass* d3d11_pass = D3D11_RETRIEVE_DRIVER_DATA_AS(pass, Direct3D11ComputePass*);

	for(uint32_t i = 0; i < num_buffers; i++)
	{
		if(is_readwrite && (buffers[i]->usage & PULSE_BUFFER_USAGE_STORAGE_WRITE) == 0)
		{
			if(PULSE_IS_BACKEND_LOW_LEVEL_DEBUG(pass->cmd->device->backend))
				PulseLogError(pass->cmd->device->backend, "cannot bind a read only buffer with read-write buffers");
			PulseSetInternalError(PULSE_ERROR_INVALID_BUFFER_USAGE);
			return;
		}
		else if(!is_readwrite && (buffers[i]->usage & PULSE_BUFFER_USAGE_STORAGE_WRITE) != 0)
		{
			if(PULSE_IS_BACKEND_LOW_LEVEL_DEBUG(pass->cmd->device->backend))
				PulseLogError(pass->cmd->device->backend, "cannot bind a read-write buffer with read only buffers");
			PulseSetInternalError(PULSE_ERROR_INVALID_BUFFER_USAGE);
			return;
		}

		if(array[i] == buffers[i])
			continue;
		array[i] = buffers[i];

		if(is_readwrite)
			d3d11_pass->should_bind_write_resources = true;
		else
			d3d11_pass->should_bind_read_only_resources = true;
	}
}

void Direct3D11BindUniformData(PulseComputePass pass, uint32_t slot, const void* data, uint32_t data_size)
{
}

void Direct3D11BindStorageImages(PulseComputePass pass, const PulseImage* images, uint32_t num_images)
{
}

void Direct3D11BindComputePipeline(PulseComputePass pass, PulseComputePipeline pipeline)
{
	Direct3D11ComputePass* d3d11_pass = D3D11_RETRIEVE_DRIVER_DATA_AS(pass, Direct3D11ComputePass*);
	Direct3D11CommandList* d3d11_cmd = D3D11_RETRIEVE_DRIVER_DATA_AS(pass->cmd, Direct3D11CommandList*);
	Direct3D11ComputePipeline* d3d11_pipeline = D3D11_RETRIEVE_DRIVER_DATA_AS(pipeline, Direct3D11ComputePipeline*);
	ID3D11DeviceContext_CSSetShader(d3d11_cmd->context, d3d11_pipeline->shader, PULSE_NULLPTR, 0);

	d3d11_pass->should_bind_read_only_resources = true;
	d3d11_pass->should_bind_write_resources = true;
	d3d11_pass->should_bind_uniform_resources = true;
}

void Direct3D11DispatchComputations(PulseComputePass pass, uint32_t groupcount_x, uint32_t groupcount_y, uint32_t groupcount_z)
{
	Direct3D11ComputePass* d3d11_pass = D3D11_RETRIEVE_DRIVER_DATA_AS(pass, Direct3D11ComputePass*);
	Direct3D11CommandList* d3d11_cmd = D3D11_RETRIEVE_DRIVER_DATA_AS(pass->cmd, Direct3D11CommandList*);
	Direct3D11BindResources(pass);
	ID3D11DeviceContext_Dispatch(d3d11_cmd->context, groupcount_x, groupcount_y, groupcount_z);
}
