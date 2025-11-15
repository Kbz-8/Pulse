// Copyright (C) 2025 kbz_8
// This file is part of "Pulse"
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Pulse.h>

#ifdef PULSE_ENABLE_METAL_BACKEND

#ifndef PULSE_METAL_H_
#define PULSE_METAL_H_

#define METAL_RETRIEVE_DRIVER_DATA_AS(handle, cast) ((cast)handle->driver_data)

#define CHECK_METAL_RETVAL(backend, handle, error, retval) \
	do { \
		if(!(handle)) \
		{ \
			if(backend != PULSE_NULL_HANDLE && PULSE_IS_BACKEND_LOW_LEVEL_DEBUG(backend)) \
				PulseLogError(backend, "(Metal) call to a Metal function failed"); \
			PulseSetInternalError(error); \
			return retval; \
		} \
	} while(0) \

#define CHECK_METAL(backend, handle, error) CHECK_METAL_RETVAL(backend, handle, error, )

PulseBackendFlags MetalCheckSupport(PulseBackendFlags candidates, PulseShaderFormatsFlags shader_formats_used); // Returns corresponding PULSE_BACKEND enum in case of success and PULSE_BACKEND_INVALID otherwise

#endif // PULSE_METAL_H_

#endif // PULSE_ENABLE_METAL_BACKEND
