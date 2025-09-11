RWStructuredBuffer<uint> write_ssbo : register(u0);

[numthreads(16, 16, 1)]
void main(uint3 grid : SV_DispatchThreadID)
{
    write_ssbo[grid.x * grid.y] = 0xFFFFFFFFu;
}
