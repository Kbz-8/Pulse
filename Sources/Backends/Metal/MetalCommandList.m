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
	@autoreleasepool
	{
		PULSE_UNUSED(usage);

		MetalDevice* metal_device = (MetalDevice*)METAL_RETRIEVE_DRIVER_DATA_AS(device, MetalDevice*);

		PulseCommandList cmd = (PulseCommandList)calloc(1, sizeof(PulseCommandListHandler));
		PULSE_CHECK_ALLOCATION_RETVAL(cmd, PULSE_NULL_HANDLE);

		MetalCommandList* metal_cmd = (MetalCommandList*)calloc(1, sizeof(MetalCommandList));
		PULSE_CHECK_ALLOCATION_RETVAL(metal_cmd, PULSE_NULL_HANDLE);

		metal_cmd->cmd = [metal_device->queue commandBuffer];

		cmd->driver_data = metal_cmd;
		return cmd;
	}
}

bool MetalSubmitCommandList(PulseDevice device, PulseCommandList cmd, PulseFence fence)
{
}

void MetalReleaseCommandList(PulseDevice device, PulseCommandList cmd)
{
	@autoreleasepool
	{
		PULSE_UNUSED(device);
		MetalCommandList* metal_cmd = METAL_RETRIEVE_DRIVER_DATA_AS(cmd, MetalCommandList*);
		metal_cmd->cmd = nil;
		free(metal_cmd);
		free(cmd);
	}
}
