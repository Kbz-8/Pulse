// Copyright (C) 2025 kanel
// This file is part of "Pulse"
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Pulse.h>
#include "../../PulseInternal.h"
#include "D3D11.h"
#include "D3D11Device.h"
#include "D3D11Fence.h"
#include "D3D11CommandList.h"

PulseFence Direct3D11CreateFence(PulseDevice device)
{
	Direct3D11Device* d3d11_device = D3D11_RETRIEVE_DRIVER_DATA_AS(device, Direct3D11Device*);

	PulseFence fence = (PulseFence)calloc(1, sizeof(PulseFence));
	PULSE_CHECK_ALLOCATION_RETVAL(fence, PULSE_NULL_HANDLE);
	Direct3D11Fence* d3d11_fence = (Direct3D11Fence*)calloc(1, sizeof(Direct3D11Fence));
	PULSE_CHECK_ALLOCATION_RETVAL(d3d11_fence, PULSE_NULL_HANDLE);

	D3D11_QUERY_DESC query_descriptor = {};
	query_descriptor.Query = D3D11_QUERY_EVENT;   // becomes signaled when all prior work completes
	query_descriptor.MiscFlags = 0;
	CHECK_D3D11_RETVAL(device->backend, ID3D11Device_CreateQuery(d3d11_device->device, &query_descriptor, &d3d11_fence->query), PULSE_ERROR_INITIALIZATION_FAILED, PULSE_NULL_HANDLE);

	fence->driver_data = d3d11_fence;

	return fence;
}

void Direct3D11DestroyFence(PulseDevice device, PulseFence fence)
{
	PULSE_UNUSED(device);
	Direct3D11Fence* d3d11_fence = D3D11_RETRIEVE_DRIVER_DATA_AS(fence, Direct3D11Fence*);
	ID3D11Query_Release(d3d11_fence->query);
	free(d3d11_fence);
	free(fence);
}

bool Direct3D11IsFenceReady(PulseDevice device, PulseFence fence)
{
	Direct3D11Device* d3d11_device = D3D11_RETRIEVE_DRIVER_DATA_AS(device, Direct3D11Device*);
	Direct3D11Fence* d3d11_fence = D3D11_RETRIEVE_DRIVER_DATA_AS(fence, Direct3D11Fence*);
	BOOL done = FALSE;
	HRESULT res = ID3D11DeviceContext_GetData(d3d11_device->context, (ID3D11Asynchronous*)d3d11_fence->query, &done, sizeof(done), D3D11_ASYNC_GETDATA_DONOTFLUSH);
	return res == S_OK && done == TRUE;
}

bool Direct3D11WaitForFences(PulseDevice device, const PulseFence* fences, uint32_t fences_count, bool wait_for_all)
{
	PULSE_UNUSED(device);
	if(fences_count == 0)
		return true;
	uint32_t fences_to_wait = fences_count;
	while(fences_to_wait != 0)
	{
		for(uint32_t i = 0; i < fences_count; i++)
		{
			if(Direct3D11IsFenceReady(device, fences[i]))
				fences_to_wait--;
		}
		if(!wait_for_all && fences_to_wait != fences_count)
			return true;
		PulseSleep(1); // 1ms
	}
	return true;
}
