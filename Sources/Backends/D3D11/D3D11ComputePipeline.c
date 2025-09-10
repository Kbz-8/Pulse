// Copyright (C) 2025 kanel
// This file is part of "Pulse"
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Pulse.h>
#include "../../PulseInternal.h"
#include "D3D11.h"
#include "D3D11Device.h"
#include "D3D11ComputePipeline.h"
#include <string.h>

#ifndef PULSE_D3D11_COMPILER_UNAVAILABLE
	#include <d3dcompiler.h>

	static HRESULT CompileComputeShader(PulseDevice device, const unsigned char* src, uint32_t src_size, const char* entry_point, ID3DBlob** blob)
	{
		if(!src || !entry_point || !device || !blob)
		   return E_INVALIDARG;

		Direct3D11Device* d3d11_device = D3D11_RETRIEVE_DRIVER_DATA_AS(device, Direct3D11Device*);
		*blob = PULSE_NULLPTR;

		UINT flags = D3DCOMPILE_ENABLE_STRICTNESS;
		if(PULSE_IS_BACKEND_HIGH_LEVEL_DEBUG(device->backend))
			flags |= D3DCOMPILE_DEBUG;

		// We generally prefer to use the higher CS shader profile when possible as CS 5.0 is better performance on 11-class hardware
		LPCSTR profile = (ID3D11Device_GetFeatureLevel(d3d11_device->device) >= D3D_FEATURE_LEVEL_11_0) ? "cs_5_0" : "cs_4_0";

		ID3DBlob* shader_blob = PULSE_NULLPTR;
		ID3DBlob* error_blob = PULSE_NULLPTR;
		HRESULT hr = D3DCompile(src, src_size, PULSE_NULLPTR, PULSE_NULLPTR, PULSE_NULLPTR, entry_point, profile, flags, 0, &shader_blob, &error_blob);

		if(FAILED(hr))
		{
			if(error_blob)
			{
				if(PULSE_IS_BACKEND_LOW_LEVEL_DEBUG(device->backend))
					PulseLogInfoFmt(device->backend, "(D3D11) failed to compile HLSL shader. %s", ID3D10Blob_GetBufferPointer(error_blob));
				ID3D10Blob_Release(error_blob);
			}
			if(shader_blob)
				ID3D10Blob_Release(shader_blob);
			return hr;
		}

		*blob = shader_blob;
		return hr;
	}
#else
	static HRESULT CompileComputeShader(PulseDevice device, const unsigned char* src, uint32_t src_size, const char* entry_point, ID3DBlob** blob)
	{
		if(PULSE_IS_BACKEND_LOW_LEVEL_DEBUG(device->backend))
			PulseLogInfo(device->backend, "(D3D11) on-the-fly shader compilation is not available");
		PulseSetInternalError(PULSE_ERROR_INITIALIZATION_FAILED);
		return D3DERR_INVALIDCALL;
	}
#endif

PulseComputePipeline Direct3D11CreateComputePipeline(PulseDevice device, const PulseComputePipelineCreateInfo* info)
{
	Direct3D11Device* d3d11_device = D3D11_RETRIEVE_DRIVER_DATA_AS(device, Direct3D11Device*);

	PulseComputePipelineHandler* pipeline = (PulseComputePipelineHandler*)calloc(1, sizeof(PulseComputePipelineHandler));
	PULSE_CHECK_ALLOCATION_RETVAL(pipeline, PULSE_NULL_HANDLE);

	Direct3D11ComputePipeline* d3d11_pipeline = (Direct3D11ComputePipeline*)calloc(1, sizeof(Direct3D11ComputePipeline));
	PULSE_CHECK_ALLOCATION_RETVAL(d3d11_pipeline, PULSE_NULL_HANDLE);

	pipeline->driver_data = d3d11_pipeline;

	void* bytecode_data = PULSE_NULLPTR;
	size_t bytecode_size;

	if(info->format & PULSE_SHADER_FORMAT_HLSL_BIT)
	{
		ID3D10Blob* blob = PULSE_NULLPTR;
		CHECK_D3D11_RETVAL(device->backend, CompileComputeShader(device, info->code, info->code_size, info->entrypoint, &blob), PULSE_ERROR_INITIALIZATION_FAILED, PULSE_NULL_HANDLE);
		bytecode_size = ID3D10Blob_GetBufferSize(blob);
		memcpy(bytecode_data, ID3D10Blob_GetBufferPointer(blob), bytecode_size);
		ID3D10Blob_Release(blob);
	}

	if(bytecode_data == PULSE_NULLPTR)
	{
		bytecode_data = (void*)info->code;
		bytecode_size = info->code_size;
	}

	CHECK_D3D11_RETVAL(device->backend, ID3D11Device_CreateComputeShader(d3d11_device->device, bytecode_data, bytecode_size, PULSE_NULLPTR, &d3d11_pipeline->shader), PULSE_ERROR_INITIALIZATION_FAILED, PULSE_NULL_HANDLE);;

	if(PULSE_IS_BACKEND_HIGH_LEVEL_DEBUG(device->backend))
		PulseLogInfoFmt(device->backend, "(D3D11) created new compute pipeline %p", pipeline);
	return pipeline;
}

void Direct3D11DestroyComputePipeline(PulseDevice device, PulseComputePipeline pipeline)
{
	if(pipeline == PULSE_NULL_HANDLE)
	{
		if(PULSE_IS_BACKEND_LOW_LEVEL_DEBUG(device->backend))
			PulseLogWarning(device->backend, "compute pipeline is NULL, this may be a bug in your application");
		return;
	}
	Direct3D11ComputePipeline* d3d11_pipeline = D3D11_RETRIEVE_DRIVER_DATA_AS(pipeline, Direct3D11ComputePipeline*);
	ID3D11ComputeShader_Release(d3d11_pipeline->shader);
	free(d3d11_pipeline);
	if(PULSE_IS_BACKEND_HIGH_LEVEL_DEBUG(device->backend))
		PulseLogInfoFmt(device->backend, "(D3D11) destroyed compute pipeline %p", pipeline);
	free(pipeline);
}
