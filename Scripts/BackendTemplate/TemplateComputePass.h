// Copyright (C) 2025 kbz_8
// This file is part of "Pulse"
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Pulse.h>

#ifdef PULSE_ENABLE_TEMPLATE_BACKEND

#ifndef PULSE_TEMPLATE_COMPUTE_PASS_H_
#define PULSE_TEMPLATE_COMPUTE_PASS_H_

#include "Template.h"

typedef struct MetalComputePass
{
	int dummy;
} MetalComputePass;

PulseComputePass TemplateNameCreateComputePass(PulseDevice device, PulseCommandList cmd);
void TemplateNameDestroyComputePass(PulseDevice device, PulseComputePass pass);

PulseComputePass TemplateNameBeginComputePass(PulseCommandList cmd);
void TemplateNameEndComputePass(PulseComputePass pass);
void TemplateNameBindStorageBuffers(PulseComputePass pass, const PulseBuffer* buffers, uint32_t num_buffers);
void TemplateNameBindUniformData(PulseComputePass pass, uint32_t slot, const void* data, uint32_t data_size);
void TemplateNameBindStorageImages(PulseComputePass pass, const PulseImage* images, uint32_t num_images);
void TemplateNameBindComputePipeline(PulseComputePass pass, PulseComputePipeline pipeline);
void TemplateNameDispatchComputations(PulseComputePass pass, uint32_t groupcount_x, uint32_t groupcount_y, uint32_t groupcount_z);

#endif // PULSE_TEMPLATE_COMPUTE_PASS_H_

#endif // PULSE_ENABLE_TEMPLATE_BACKEND
