#include <Pulse.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HLSL_SOURCE(...) #__VA_ARGS__

void DebugCallBack(PulseDebugMessageSeverity severity, const char* message)
{
	if(severity == PULSE_DEBUG_MESSAGE_SEVERITY_ERROR)
	{
		fprintf(stderr, "Pulse Error: %s\n", message);
		exit(1);
	}
	else if(severity == PULSE_DEBUG_MESSAGE_SEVERITY_WARNING)
		fprintf(stderr, "Pulse Warning: %s\n", message);
	else
		printf("Pulse: %s\n", message);
}

#define BUFFER_SIZE (256 * sizeof(uint32_t))

const char* hlsl_source = HLSL_SOURCE(
	RWStructuredBuffer<int> ssbo : register(u0);

	[numthreads(16, 16, 1)]
	void CSMain(uint3 grid : SV_DispatchThreadID)
	{
		ssbo[grid.x * grid.y] = (int)(grid.x * grid.y);
	}
);

int main(void)
{
	PulseBackend backend = PulseLoadBackend(PULSE_BACKEND_D3D11, PULSE_SHADER_FORMAT_HLSL_BIT, PULSE_HIGH_DEBUG);
	PulseSetDebugCallback(backend, DebugCallBack);
	PulseDevice device = PulseCreateDevice(backend, NULL, 0);

	PulseBufferCreateInfo buffer_create_info = { 0 };
	buffer_create_info.size = BUFFER_SIZE;
	buffer_create_info.usage = PULSE_BUFFER_USAGE_STORAGE_READ | PULSE_BUFFER_USAGE_STORAGE_WRITE | PULSE_BUFFER_USAGE_TRANSFER_DOWNLOAD;
	PulseBuffer buffer = PulseCreateBuffer(device, &buffer_create_info);

	// GPU computations
	{
		PulseComputePipelineCreateInfo info = { 0 };
		info.code_size = strlen(hlsl_source);
		info.code = (const uint8_t*)hlsl_source;
		info.entrypoint = "CSMain";
		info.format = PULSE_SHADER_FORMAT_HLSL_BIT;
		info.num_readwrite_storage_buffers = 1;
		PulseComputePipeline pipeline = PulseCreateComputePipeline(device, &info);

		PulseDestroyComputePipeline(device, pipeline);
	}

	PulseDestroyBuffer(device, buffer);

	PulseDestroyDevice(device);
	PulseUnloadBackend(backend);
	puts("Successfully executed Pulse example using D3D11 !");
	return 0;
}
