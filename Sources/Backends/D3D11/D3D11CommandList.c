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
	PULSE_CHECK_HANDLE_RETVAL(device, PULSE_NULL_HANDLE);
	PulseCommandList cmd = (PulseCommandList)calloc(1, sizeof(PulseCommandListHandler));
	PULSE_CHECK_ALLOCATION_RETVAL(cmd, PULSE_NULL_HANDLE);
	return cmd;
}

bool Direct3D11SubmitCommandList(PulseDevice device, PulseCommandList cmd, PulseFence fence)
{
}

void Direct3D11ReleaseCommandList(PulseDevice device, PulseCommandList cmd)
{
}
