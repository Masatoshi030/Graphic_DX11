#include "common.hlsl"

PS_IN vs_main(VS_IN input)
{
    PS_IN output;
    float3 nor;
    float col;
    
    output.posw = mul(input.Position, World);
    output.Position = mul(output.posw, View);
    output.Position = mul(output.Position, Projection);
    
    output.norw = mul(input.Normal, World);
    
    return output;
}