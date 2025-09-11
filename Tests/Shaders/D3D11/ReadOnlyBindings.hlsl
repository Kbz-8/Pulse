StructuredBuffer<uint> read_ssbo : register(t0);
Texture2D<float4> read_texture : register(t1);

[numthreads(16, 16, 1)]
void main(uint3 grid : SV_DispatchThreadID)
{
}
