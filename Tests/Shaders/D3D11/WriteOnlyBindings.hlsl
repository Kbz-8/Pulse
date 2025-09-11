RWStructuredBuffer<uint> write_ssbo : register(u0);
RWTexture2D<float4> write_texture : register(u1);

[numthreads(16, 16, 1)]
void main(uint3 grid : SV_DispatchThreadID)
{
}
