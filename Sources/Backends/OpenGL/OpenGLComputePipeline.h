// Copyright (C) 2025 kanel
// This file is part of "Pulse"
// For conditions of distribution and use, see copyright notice in LICENSE

#ifdef PULSE_ENABLE_OPENGL_BACKEND

#ifndef PULSE_OPENGL_COMPUTE_PIPELINE_H_
#define PULSE_OPENGL_COMPUTE_PIPELINE_H_

#include <Pulse.h>
#include "OpenGL.h"

typedef struct OpenGLComputePipeline
{
} OpenGLComputePipeline;

PulseComputePipeline OpenGLCreateComputePipeline(PulseDevice device, const PulseComputePipelineCreateInfo* info);
void OpenGLDestroyComputePipeline(PulseDevice device, PulseComputePipeline pipeline);

#endif // PULSE_OPENGL_COMPUTE_PIPELINE_H_

#endif // PULSE_ENABLE_OPENGL_BACKEND
