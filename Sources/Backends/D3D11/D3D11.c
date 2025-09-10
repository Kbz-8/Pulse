// Copyright (C) 2025 kanel
// This file is part of "Pulse"
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Pulse.h>
#include "../../PulseInternal.h"

#include "D3D11.h"
#include "D3D11Device.h"

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#ifndef PULSE_D3D11_COMPILER_UNAVAILABLE
	#pragma comment(lib,"d3dcompiler.lib")
#endif

PulseBackendFlags Direct3D11CheckSupport(PulseBackendFlags candidates, PulseShaderFormatsFlags shader_formats_used)
{
	if(candidates != PULSE_BACKEND_ANY && (candidates & PULSE_BACKEND_D3D11) == 0)
		return PULSE_BACKEND_INVALID;
	if((shader_formats_used & PULSE_SHADER_FORMAT_DXBC_BIT) == 0 && (shader_formats_used & PULSE_SHADER_FORMAT_HLSL_BIT) == 0)
		return PULSE_BACKEND_INVALID;
	return PULSE_BACKEND_D3D11;
}

bool Direct3D11LoadBackend(PulseBackend backend, PulseDebugLevel debug_level)
{
	PULSE_UNUSED(backend);
	PULSE_UNUSED(debug_level);
	return true;
}

void Direct3D11UnloadBackend(PulseBackend backend)
{
}

const char* D3D11VerbaliseResult(HRESULT res)
{
	switch(res)
	{
		case S_OK:
		case S_FALSE: return "success";

		case D3D11_ERROR_FILE_NOT_FOUND: return "a file was not found";
		case D3D11_ERROR_TOO_MANY_UNIQUE_STATE_OBJECTS: return "too many instances of a particular state objects";
		case D3D11_ERROR_TOO_MANY_UNIQUE_VIEW_OBJECTS: return "too many instances of a particular view objects";
		case D3D11_ERROR_DEFERRED_CONTEXT_MAP_WITHOUT_INITIAL_DISCARD: return "deffered context mapped without initial discard";
		case D3DERR_INVALIDCALL: return "invalid call";
		case D3DERR_WASSTILLDRAWING: return "was still drawing";
		case E_FAIL: return "attempted to create a device with the debug layer enabled and the layer is not installed";
		case E_INVALIDARG: return "an invalid parameter was passed to the returning function";
		case E_OUTOFMEMORY: return "could not allocate sufficient memory to complete the call";
		case E_NOTIMPL: return "method call isn't implemented with the passed parameter combination";

		default: return "Unknown D3D11 error";
	}
	return "Unknown D3D11 error"; // Just to avoid warnings
}

PulseBackendHandler D3D11Driver = {
	.PFN_LoadBackend = Direct3D11LoadBackend,
	.PFN_UnloadBackend = Direct3D11UnloadBackend,
	.PFN_CreateDevice = Direct3D11CreateDevice,
	.backend = PULSE_BACKEND_D3D11,
	.supported_shader_formats = PULSE_SHADER_FORMAT_DXBC_BIT | PULSE_SHADER_FORMAT_HLSL_BIT,
	.driver_data = PULSE_NULLPTR
};
