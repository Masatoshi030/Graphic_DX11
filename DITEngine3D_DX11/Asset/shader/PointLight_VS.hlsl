#include "common.hlsl"

PS_IN vs_main(VS_IN input)
{
    PS_IN output;
    float3 nor;
    float col;
    
    output.ViewVector = normalize(input.Position - Eye_Info.EyePosition);
    
    output.posw = mul(input.Position, World);    
    output.Position = mul(output.posw, View);
    output.Position = mul(output.Position, Projection);
    
    output.norw = mul(input.Normal, World);
    
    output.TexCoord = input.TexCoord;
    output.Diffuse = input.Diffuse * Material.Diffuse;
    
    return output;
}