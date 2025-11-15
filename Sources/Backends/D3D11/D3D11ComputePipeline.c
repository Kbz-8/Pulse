// Copyright (C) 2025 kbz_8
// This file is part of "Pulse"
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Pulse.h>
#include "../../PulseInternal.h"
#include "D3D11.h"
#include "D3D11Device.h"
#include "D3D11ComputePipeline.h"

PulseComputePipeline Direct3D11CreateComputePipeline(PulseDevice device, const PulseComputePipelineCreateInfo* info)
{
	Direct3D11Device* d3d11_device = D3D11_RETRIEVE_DRIVER_DATA_AS(device, Direct3D11Device*);

	PulseComputePipelineHandler* pipeline = (PulseComputePipelineHandler*)calloc(1, sizeof(PulseComputePipelineHandler));
	PULSE_CHECK_ALLOCATION_RETVAL(pipeline, PULSE_NULL_HANDLE);

	Direct3D11ComputePipeline* d3d11_pipeline = (Direct3D11ComputePipeline*)calloc(1, sizeof(Direct3D11ComputePipeline));
	PULSE_CHECK_ALLOCATION_RETVAL(d3d11_pipeline, PULSE_NULL_HANDLE);

	pipeline->driver_data = d3d11_pipeline;

	CHECK_D3D11_RETVAL(device->backend, ID3D11Device_CreateComputeShader(d3d11_device->device, (void*)info->code, info->code_size, PULSE_NULLPTR, &d3d11_pipeline->shader), PULSE_ERROR_INITIALIZATION_FAILED, PULSE_NULL_HANDLE);;

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
