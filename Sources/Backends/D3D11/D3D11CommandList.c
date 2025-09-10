// Copyright (C) 2025 kanel
// This file is part of "Pulse"
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Pulse.h>
#include "../../PulseInternal.h"
#include "D3D11.h"
#include "D3D11Fence.h"
#include "D3D11Device.h"
#include "D3D11CommandList.h"
#include "D3D11ComputePass.h"
#include "D3D11ComputePipeline.h"
#include "D3D11Buffer.h"

PulseCommandList Direct3D11RequestCommandList(PulseDevice device, PulseCommandListUsage usage)
{
	Direct3D11Device* d3d11_device = D3D11_RETRIEVE_DRIVER_DATA_AS(device, Direct3D11Device*);

	PulseCommandList cmd = (PulseCommandList)calloc(1, sizeof(PulseCommandListHandler));
	PULSE_CHECK_ALLOCATION_RETVAL(cmd, PULSE_NULL_HANDLE);
	Direct3D11CommandList* d3d11_cmd = (Direct3D11CommandList*)calloc(1, sizeof(Direct3D11CommandList));
	PULSE_CHECK_ALLOCATION_RETVAL(d3d11_cmd, PULSE_NULL_HANDLE);

	CHECK_D3D11_RETVAL(device->backend, ID3D11Device_CreateDeferredContext(d3d11_device->device, 0, &d3d11_cmd->context), PULSE_ERROR_INITIALIZATION_FAILED, PULSE_NULL_HANDLE);

	cmd->usage = usage;
	cmd->device = device;
	cmd->driver_data = d3d11_cmd;
	cmd->thread_id = PulseGetThreadID();

	cmd->pass = Direct3D11CreateComputePass(device, cmd);
	cmd->state = PULSE_COMMAND_LIST_STATE_RECORDING;
	cmd->is_available = false;

	return cmd;
}

bool Direct3D11SubmitCommandList(PulseDevice device, PulseCommandList cmd, PulseFence fence)
{
	Direct3D11Device* d3d11_device = D3D11_RETRIEVE_DRIVER_DATA_AS(device, Direct3D11Device*);
	Direct3D11CommandList* d3d11_cmd = D3D11_RETRIEVE_DRIVER_DATA_AS(cmd, Direct3D11CommandList*);
	ID3D11CommandList* command_list;

	if(fence != PULSE_NULL_HANDLE)
	{
		Direct3D11Fence* d3d11_fence = D3D11_RETRIEVE_DRIVER_DATA_AS(fence, Direct3D11Fence*);
		fence->cmd = cmd;
		ID3D11DeviceContext_End(d3d11_device->context, (ID3D11Asynchronous*)d3d11_fence->query); // Signal fence now
	}

	HRESULT res = ID3D11DeviceContext_FinishCommandList(d3d11_cmd->context, false, &command_list);
	switch(res)
	{
		case S_OK:
		case S_FALSE: break;

		case DXGI_ERROR_DEVICE_REMOVED: PulseSetInternalError(PULSE_ERROR_DEVICE_LOST); return false;
		case E_OUTOFMEMORY: PulseSetInternalError(PULSE_ERROR_DEVICE_ALLOCATION_FAILED); return false;
		case DXGI_ERROR_INVALID_CALL: PulseSetInternalError(PULSE_ERROR_CPU_ALLOCATION_FAILED); return false;
		default: return false;
	}
	ID3D11DeviceContext_ExecuteCommandList(d3d11_device->context, command_list, false);
	ID3D11CommandList_Release(command_list);
	return true;
}

void Direct3D11ReleaseCommandList(PulseDevice device, PulseCommandList cmd)
{
	Direct3D11CommandList* d3d11_cmd = D3D11_RETRIEVE_DRIVER_DATA_AS(cmd, Direct3D11CommandList*);
	ID3D11DeviceContext_Release(d3d11_cmd->context);
	Direct3D11DestroyComputePass(device, cmd->pass);
	free(d3d11_cmd);
	free(cmd);
}
