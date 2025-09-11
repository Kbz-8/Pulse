#include "Common.h"

#include <unity/unity.h>
#include <Pulse.h>

void TestDeviceSetup()
{
	PulseBackend backend;
	SetupPulse(&backend);

	PulseDevice device = PulseCreateDevice(backend, NULL, 0);
	TEST_ASSERT_NOT_EQUAL_MESSAGE(device, PULSE_NULL_HANDLE, PulseVerbaliseErrorType(PulseGetLastErrorType()));
	PulseDestroyDevice(device);

	CleanupPulse(backend);
}

void TestMultipleDevices()
{
	PulseBackend backend;
	SetupPulse(&backend);

	#define DEVICES_COUNT 10

	PulseDevice devices[DEVICES_COUNT];
	for(int i = 0; i < DEVICES_COUNT; i++)
	{
		devices[i] = PulseCreateDevice(backend, NULL, 0);
		TEST_ASSERT_NOT_EQUAL_MESSAGE(devices[i], PULSE_NULL_HANDLE, PulseVerbaliseErrorType(PulseGetLastErrorType()));
	}

	for(int i = 0; i < DEVICES_COUNT; i++)
		PulseDestroyDevice(devices[i]);

	#undef DEVICES_COUNT
	CleanupPulse(backend);
}

void TestForbiddenDeviceSetup()
{
	PulseBackend backend;
	SetupPulse(&backend);

	PulseDevice device1 = PulseCreateDevice(backend, NULL, 0);
	TEST_ASSERT_NOT_EQUAL_MESSAGE(device1, PULSE_NULL_HANDLE, PulseVerbaliseErrorType(PulseGetLastErrorType()));

	PulseDevice device2 = PulseCreateDevice(backend, &device1, 1);
	TEST_ASSERT_NOT_EQUAL(device2, device1);

	PulseDestroyDevice(device2);
	PulseDestroyDevice(device1);

	CleanupPulse(backend);
}

void TestInvalidBackendDeviceSetup()
{
	PulseDevice device= PulseCreateDevice(PULSE_NULL_HANDLE, NULL, 0);
	TEST_ASSERT_EQUAL(device, PULSE_NULL_HANDLE);
	PulseDestroyDevice(device);
}

void TestBackendInUse()
{
	PulseBackend backend;
	SetupPulse(&backend);

	PulseDevice device = PulseCreateDevice(backend, NULL, 0);
	TEST_ASSERT_NOT_EQUAL_MESSAGE(device, PULSE_NULL_HANDLE, PulseVerbaliseErrorType(PulseGetLastErrorType()));
	#if defined(VULKAN_ENABLED)
		TEST_ASSERT_EQUAL(PulseGetBackendInUseByDevice(device), PULSE_BACKEND_VULKAN);
	#elif defined(WEBGPU_ENABLED)
		TEST_ASSERT_EQUAL(PulseGetBackendInUseByDevice(device), PULSE_BACKEND_WEBGPU);
	#elif defined(OPENGL_ENABLED)
		TEST_ASSERT_EQUAL(PulseGetBackendInUseByDevice(device), PULSE_BACKEND_OPENGL);
	#elif defined(OPENGLES_ENABLED)
		TEST_ASSERT_EQUAL(PulseGetBackendInUseByDevice(device), PULSE_BACKEND_OPENGL_ES);
	#elif defined(D3D11_ENABLED)
		TEST_ASSERT_EQUAL(PulseGetBackendInUseByDevice(device), PULSE_BACKEND_D3D11);
	#endif
	PulseDestroyDevice(device);

	CleanupPulse(backend);
}

void TestShaderFormatSupport()
{
	PulseBackend backend;
	SetupPulse(&backend);

	PulseDevice device = PulseCreateDevice(backend, NULL, 0);
	TEST_ASSERT_NOT_EQUAL_MESSAGE(device, PULSE_NULL_HANDLE, PulseVerbaliseErrorType(PulseGetLastErrorType()));
	#if defined(VULKAN_ENABLED)
		TEST_ASSERT_TRUE(PulseDeviceSupportsShaderFormats(device, PULSE_SHADER_FORMAT_SPIRV_BIT));
	#elif defined(WEBGPU_ENABLED)
		TEST_ASSERT_TRUE(PulseDeviceSupportsShaderFormats(device, PULSE_SHADER_FORMAT_WGSL_BIT));
	#elif defined(OPENGL_ENABLED)
		TEST_ASSERT_TRUE(PulseDeviceSupportsShaderFormats(device, PULSE_SHADER_FORMAT_GLSL_BIT));
	#elif defined(OPENGLES_ENABLED)
		TEST_ASSERT_TRUE(PulseDeviceSupportsShaderFormats(device, PULSE_SHADER_FORMAT_GLSL_BIT));
	#elif defined(D3D11_ENABLED)
		TEST_ASSERT_TRUE(PulseDeviceSupportsShaderFormats(device, PULSE_SHADER_FORMAT_DXBC_BIT));
	#endif
	PulseDestroyDevice(device);

	CleanupPulse(backend);
}

void TestDevice()
{
	RUN_TEST(TestDeviceSetup);
	RUN_TEST(TestForbiddenDeviceSetup);
	RUN_TEST(TestInvalidBackendDeviceSetup);
	RUN_TEST(TestMultipleDevices);
	RUN_TEST(TestBackendInUse);
	RUN_TEST(TestShaderFormatSupport);
}
