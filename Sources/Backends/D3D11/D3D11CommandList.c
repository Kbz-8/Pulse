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

	cmd->pass = PULSE_NULL_HANDLE;
	cmd->state = PULSE_COMMAND_LIST_STATE_RECORDING;
	cmd->is_available = false;

	return cmd;
}

bool Direct3D11SubmitCommandList(PulseDevice device, PulseCommandList cmd, PulseFence fence)
{
}

void Direct3D11ReleaseCommandList(PulseDevice device, PulseCommandList cmd)
{
	PULSE_UNUSED(device);
	Direct3D11CommandList* d3d11_cmd = D3D11_RETRIEVE_DRIVER_DATA_AS(cmd, Direct3D11CommandList*);
	ID3D11DeviceContext_Release(d3d11_cmd->context);
	free(d3d11_cmd);
	free(cmd);
}
