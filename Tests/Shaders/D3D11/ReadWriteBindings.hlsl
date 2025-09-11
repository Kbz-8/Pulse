Texture2D<float4>        read_texture  : register(t0);
StructuredBuffer<uint>   read_ssbo     : register(t1);
RWTexture2D<float4>      write_texture : register(u0);
RWStructuredBuffer<uint> write_ssbo    : register(u1);

[numthreads(16, 16, 1)]
void main(uint3 grid : SV_DispatchThreadID)
{
}
