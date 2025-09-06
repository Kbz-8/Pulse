// Copyright (C) 2025 kanel
// This file is part of "Pulse"
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Pulse.h>
#include "../../PulseInternal.h"
#include "Metal.h"
#include "MetalFence.h"
#include "MetalDevice.h"
#include "MetalCommandList.h"
#include "MetalComputePass.h"
#include "MetalComputePipeline.h"
#include "MetalBuffer.h"

PulseCommandList MetalRequestCommandList(PulseDevice device, PulseCommandListUsage usage)
{
	PULSE_CHECK_HANDLE_RETVAL(device, PULSE_NULL_HANDLE);
	PulseCommandList cmd = (PulseCommandList)calloc(1, sizeof(PulseCommandListHandler));
	PULSE_CHECK_ALLOCATION_RETVAL(cmd, PULSE_NULL_HANDLE);
	return cmd;
}

bool MetalSubmitCommandList(PulseDevice device, PulseCommandList cmd, PulseFence fence)
{
}

void MetalReleaseCommandList(PulseDevice device, PulseCommandList cmd)
{
}
