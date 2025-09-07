// Copyright (C) 2025 kanel
// This file is part of "Pulse"
// For conditions of distribution and use, see copyright notice in LICENSE

#include <string.h>
#include <Pulse.h>
#include "../../PulseInternal.h"
#include "Metal.h"
#include "MetalDevice.h"
#include "MetalComputePipeline.h"

typedef struct MetalLibraryFunction
{
	id<MTLLibrary> library;
	id<MTLFunction> function;
} MetalLibraryFunction;

static bool MetalIsValidMetalLibrary(const uint8_t* code, uint32_t code_size)
{
    // Metal libraries have a 4 byte header containing `MTLB`.
    if(code_size < 4 || code == PULSE_NULLPTR)
        return false;
    return memcmp(code, "MTLB", 4) == 0;
}

static MetalLibraryFunction MetalCompileShader(PulseDevice device, const PulseComputePipelineCreateInfo* info)
{
	MetalDevice* metal_device = (MetalDevice*)METAL_RETRIEVE_DRIVER_DATA_AS(device, MetalDevice*);

	MetalLibraryFunction library_function = { nil, nil };
	id<MTLLibrary> library;
	NSError* error;

	const char* entrypoint = (info->entrypoint == PULSE_NULLPTR) ? "main0" : info->entrypoint;

	if(info->format == PULSE_SHADER_FORMAT_MSL_BIT)
	{
		NSString* code_string = [[NSString alloc] initWithBytes:info->code length:info->code_size encoding:NSUTF8StringEncoding];
		library = [metal_device->device newLibraryWithSource:code_string options:nil error:&error];
	}
	else if(info->format == PULSE_SHADER_FORMAT_METALLIB_BIT)
	{
		if(!MetalIsValidMetalLibrary(info->code, info->code_size))
		{
			if(PULSE_IS_BACKEND_LOW_LEVEL_DEBUG(device->backend))
				PulseLogError(device->backend, "(Metal) provided shader code is not a valid Metal library");
			return library_function;
		}
		dispatch_data_t data = dispatch_data_create(info->code, info->code_size, dispatch_get_global_queue(0, 0), DISPATCH_DATA_DESTRUCTOR_DEFAULT);
		library = [metal_device->device newLibraryWithData:data error:&error];
	}

	if(library == nil)
	{
		if(PULSE_IS_BACKEND_LOW_LEVEL_DEBUG(device->backend))
			PulseLogErrorFmt(device->backend, "(Metal) creating MTLLibrary failed due to %s", [[error description] cStringUsingEncoding:[NSString defaultCStringEncoding]]);
		return library_function;
	}
	else if(error != nil && PULSE_IS_BACKEND_LOW_LEVEL_DEBUG(device->backend))
		PulseLogWarningFmt(device->backend, "(Metal) creating MTLLibrary failed due to %s", [[error description] cStringUsingEncoding:[NSString defaultCStringEncoding]]);

	id<MTLFunction> function = [library newFunctionWithName:@(entrypoint)];
	if(function == nil)
	{
		PulseLogError(device->backend, "(Metal) creating MTLLibrary failed");
		return library_function;
	}

	library_function.library = library;
	library_function.function = function;
	return library_function;
}

PulseComputePipeline MetalCreateComputePipeline(PulseDevice device, const PulseComputePipelineCreateInfo* info)
{
	@autoreleasepool
	{
		MetalDevice* metal_device = (MetalDevice*)METAL_RETRIEVE_DRIVER_DATA_AS(device, MetalDevice*);

		PulseComputePipelineHandler* pipeline = (PulseComputePipelineHandler*)calloc(1, sizeof(PulseComputePipelineHandler));
		PULSE_CHECK_ALLOCATION_RETVAL(pipeline, PULSE_NULL_HANDLE);

		MetalComputePipeline* metal_pipeline = (MetalComputePipeline*)calloc(1, sizeof(MetalComputePipeline));
		PULSE_CHECK_ALLOCATION_RETVAL(metal_pipeline, PULSE_NULL_HANDLE);

		pipeline->driver_data = metal_pipeline;

		MetalLibraryFunction library_function = MetalCompileShader(device, info);
		if(library_function.library == nil || library_function.function == nil)
		{
			if(PULSE_IS_BACKEND_LOW_LEVEL_DEBUG(device->backend))
				PulseLogError(device->backend, "(Metal) failed to compile shader");
			PulseSetInternalError(PULSE_ERROR_INITIALIZATION_FAILED);
			return PULSE_NULL_HANDLE;
		}

		MTLComputePipelineDescriptor* descriptor = [MTLComputePipelineDescriptor new];
		descriptor.computeFunction = library_function.function;

		NSError* error;
		metal_pipeline->pipeline = [metal_device->device newComputePipelineStateWithDescriptor:descriptor options:MTLPipelineOptionNone reflection: nil error:&error];
		if(error)
		{
			if(PULSE_IS_BACKEND_LOW_LEVEL_DEBUG(device->backend))
				PulseLogErrorFmt(device->backend, "(Metal) failed to create compute compute pipeline; %s", [[error description] UTF8String]);
			PulseSetInternalError(PULSE_ERROR_INITIALIZATION_FAILED);
			return PULSE_NULL_HANDLE;
		}

		if(PULSE_IS_BACKEND_HIGH_LEVEL_DEBUG(device->backend))
			PulseLogInfoFmt(device->backend, "(Metal) created new compute pipeline %p", pipeline);
		return pipeline;
	}
}

void MetalDestroyComputePipeline(PulseDevice device, PulseComputePipeline pipeline)
{
	@autoreleasepool
	{
		MetalComputePipeline* metal_pipeline = METAL_RETRIEVE_DRIVER_DATA_AS(pipeline, MetalComputePipeline*);
		metal_pipeline->pipeline = nil;
		free(metal_pipeline);
		if(PULSE_IS_BACKEND_HIGH_LEVEL_DEBUG(device->backend))
			PulseLogInfoFmt(device->backend, "(Metal) destroyed compute pipeline %p", pipeline);
		free(pipeline);
	}
}
