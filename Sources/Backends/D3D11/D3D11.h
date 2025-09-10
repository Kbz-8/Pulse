// Copyright (C) 2025 kanel
// This file is part of "Pulse"
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Pulse.h>

#ifdef PULSE_ENABLE_D3D11_BACKEND

#ifndef PULSE_D3D11_H_
#define PULSE_D3D11_H_

#define D3D11_NO_HELPERS
#define CINTERFACE
#define COBJMACROS

#ifdef PULSE_PLAT_WINDOWS
	#include <initguid.h>
#endif
#include <d3d11.h>
#include <d3d11_1.h>
#include <dxgi.h>

#include "../../PulseInternal.h"

#define D3D11_RETRIEVE_DRIVER_DATA_AS(handle, cast) ((cast)handle->driver_data)

#define CHECK_D3D11_RETVAL(backend, res, error, retval) \
	do { \
		if((res) != S_OK && (res) != S_FALSE) \
		{ \
			if(backend != PULSE_NULL_HANDLE && PULSE_IS_BACKEND_LOW_LEVEL_DEBUG(backend)) \
				PulseLogErrorFmt(backend, "(D3D11) call to a D3D11 function failed due to %s", D3D11VerbaliseResult(res)); \
			PulseSetInternalError(error); \
			return retval; \
		} \
	} while(0) \

#define CHECK_D3D11(backend, res, error) CHECK_D3D11_RETVAL(backend, res, error, )

#ifndef D3D11_ERROR_FILE_NOT_FOUND
	#define D3D11_ERROR_FILE_NOT_FOUND 0x887C0002
#endif

#ifndef D3D11_ERROR_TOO_MANY_UNIQUE_STATE_OBJECTS
	#define D3D11_ERROR_TOO_MANY_UNIQUE_STATE_OBJECTS 0x887C0001
#endif

#ifndef D3D11_ERROR_TOO_MANY_UNIQUE_VIEW_OBJECTS
	#define D3D11_ERROR_TOO_MANY_UNIQUE_VIEW_OBJECTS 0x887C0003
#endif

#ifndef D3D11_ERROR_DEFERRED_CONTEXT_MAP_WITHOUT_INITIAL_DISCARD
	#define D3D11_ERROR_DEFERRED_CONTEXT_MAP_WITHOUT_INITIAL_DISCARD 0x887C0004
#endif

#ifndef D3DERR_INVALIDCALL
	#define D3DERR_INVALIDCALL 0x887A0001
#endif

#ifndef D3DERR_WASSTILLDRAWING
	#define D3DERR_WASSTILLDRAWING 0x887A000A
#endif

const char* D3D11VerbaliseResult(HRESULT res);

PulseBackendFlags Direct3D11CheckSupport(PulseBackendFlags candidates, PulseShaderFormatsFlags shader_formats_used); // Returns corresponding PULSE_BACKEND enum in case of success and PULSE_BACKEND_INVALID otherwise

#endif // PULSE_D3D11_H_

#endif // PULSE_ENABLE_D3D11_BACKEND
