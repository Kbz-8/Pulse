// Copyright (C) 2025 kanel
// This file is part of "Pulse"
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Pulse.h>

#ifdef PULSE_ENABLE_SOFTWARE_BACKEND

#ifndef PULSE_SOFTWARE_COMMAND_LIST_H_
#define PULSE_SOFTWARE_COMMAND_LIST_H_

#include <stdatomic.h>
#include <tinycthread.h>

#include "Soft.h"
#include "SoftEnums.h"
#include "SoftFence.h"

typedef struct SoftCommand
{
	struct SoftCommandList* cmd_list;
	SoftCommandType type;
	union
	{
		struct
		{
			const PulseImageRegion* src;
			const PulseImageRegion* dst;
		} BlitImages;

		struct
		{
			const PulseBufferRegion* src;
			const PulseBufferRegion* dst;
		} CopyBufferToBuffer;

		struct
		{
			const PulseBufferRegion* src;
			const PulseImageRegion* dst;
		} CopyBufferToImage;

		struct
		{
			const PulseImageRegion* src;
			const PulseBufferRegion* dst;
		} CopyImageToBuffer;

		struct
		{
			PulseComputePipeline pipeline;
			uint32_t groupcount_x;
			uint32_t groupcount_y;
			uint32_t groupcount_z;
			mtx_t dispatch_mutex;
		} Dispatch;

		struct
		{
			PulseComputePipeline pipeline;
			PulseBuffer buffer;
			uint32_t offset;
			mtx_t dispatch_mutex;
		} DispatchIndirect;
	};
	union
	{
		struct
		{
			uint32_t global_invocation_id[3];
			uint32_t local_invocation_id[3];
			uint32_t workgroup_count[3];
			uint32_t workgroup_index[3];
			uint32_t local_invocation_index;
		} Dipsatch;
	} Private;
} SoftCommand;

typedef struct SoftCommandList
{
	thrd_t thread;
	PulseFence fence;
	SoftCommand* commands;
	uint32_t commands_count;
	uint32_t commands_capacity;
	atomic_ullong commands_running;
} SoftCommandList;

PulseCommandList SoftRequestCommandList(PulseDevice device, PulseCommandListUsage usage);
void SoftQueueCommand(PulseCommandList cmd, SoftCommand command);
bool SoftSubmitCommandList(PulseDevice device, PulseCommandList cmd, PulseFence fence);
void SoftReleaseCommandList(PulseDevice device, PulseCommandList cmd);

#endif // PULSE_SOFTWARE_COMMAND_LIST_H_

#endif // PULSE_ENABLE_SOFTWARE_BACKEND
