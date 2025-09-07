#include <Pulse.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

const char* msl_source = 
"#include <metal_stdlib>\n \
using namespace metal;\
\
kernel void Main(device int* ssbo [[ buffer(0) ]], uint3 grid [[ thread_position_in_grid ]]) \
{ \
	uint idx = grid.x * grid.y; \
	ssbo[idx] = static_cast<int>(idx); \
}";

int main(void)
{
	PulseBackend backend = PulseLoadBackend(PULSE_BACKEND_METAL, PULSE_SHADER_FORMAT_MSL_BIT, PULSE_HIGH_DEBUG);
	PulseSetDebugCallback(backend, DebugCallBack);
	PulseDevice device = PulseCreateDevice(backend, NULL, 0);

	PulseBufferCreateInfo buffer_create_info = { 0 };
	buffer_create_info.size = BUFFER_SIZE;
	buffer_create_info.usage = PULSE_BUFFER_USAGE_STORAGE_READ | PULSE_BUFFER_USAGE_STORAGE_WRITE | PULSE_BUFFER_USAGE_TRANSFER_DOWNLOAD;
	PulseBuffer buffer = PulseCreateBuffer(device, &buffer_create_info);

	// GPU computations
	{
		PulseComputePipelineCreateInfo info = { 0 };
		info.code_size = strlen(msl_source);
		info.code = (const uint8_t*)msl_source;
		info.entrypoint = "Main";
		info.format = PULSE_SHADER_FORMAT_MSL_BIT;
		info.num_readwrite_storage_buffers = 1;
		PulseComputePipeline pipeline = PulseCreateComputePipeline(device, &info);

		PulseFence fence = PulseCreateFence(device);
		PulseCommandList cmd = PulseRequestCommandList(device, PULSE_COMMAND_LIST_GENERAL);

		PulseReleaseCommandList(device, cmd);
		PulseDestroyFence(device, fence);

		PulseDestroyComputePipeline(device, pipeline);
	}

	PulseDestroyBuffer(device, buffer);

	PulseDestroyDevice(device);
	PulseUnloadBackend(backend);
	puts("Successfully executed Pulse example using Metal !");
	return 0;
}

