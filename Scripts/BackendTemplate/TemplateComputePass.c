// Copyright (C) 2025 kanel
// This file is part of "Pulse"
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Pulse.h>
#include "../../PulseInternal.h"
#include "Template.h"
#include "TemplateComputePass.h"
#include "TemplateCommandList.h"

PulseComputePass TemplateNameCreateComputePass(PulseDevice device, PulseCommandList cmd)
{
	PULSE_UNUSED(device);
	PulseComputePass pass = (PulseComputePass)calloc(1, sizeof(PulseComputePassHandler));
	PULSE_CHECK_ALLOCATION_RETVAL(pass, PULSE_NULL_HANDLE);
	return pass;
}

void TemplateNameDestroyComputePass(PulseDevice device, PulseComputePass pass)
{
}

PulseComputePass TemplateNameBeginComputePass(PulseCommandList cmd)
{
}

void TemplateNameEndComputePass(PulseComputePass pass)
{
}

void TemplateNameBindStorageBuffers(PulseComputePass pass, const PulseBuffer* buffers, uint32_t num_buffers)
{
}

void TemplateNameBindUniformData(PulseComputePass pass, uint32_t slot, const void* data, uint32_t data_size)
{
}

void TemplateNameBindStorageImages(PulseComputePass pass, const PulseImage* images, uint32_t num_images)
{
}

void TemplateNameBindComputePipeline(PulseComputePass pass, PulseComputePipeline pipeline)
{
}

void TemplateNameDispatchComputations(PulseComputePass pass, uint32_t groupcount_x, uint32_t groupcount_y, uint32_t groupcount_z)
{
}
