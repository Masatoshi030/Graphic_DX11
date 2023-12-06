#include "common.hlsl"

Texture2D g_Texture : register(t0);
SamplerState g_SamplerState : register(s0);

float4 ps_main(PS_IN input) : SV_Target
{
    float3 dir;
    float len;
    float colD;
    float colA;
    float col;
    
    //“_ŒõŒ¹‚Ì•ûŒü
    dir = Light_Point.Position.xyz - input.posw.xyz;
    
    //“_ŒõŒ¹‚Ì‹——£
    len = length(dir);
    
    //“_ŒõŒ¹‚Ì•ûŒü‚ğ³‹K‰»
    dir = dir / len;
    
    //ŠgU
    colD = saturate(dot(normalize(input.norw.xyz), dir));
    
    //Œ¸Š
    colA = saturate(1.0f / (Light_Point.Attenuation.x + Light_Point.Attenuation.y * len + Light_Point.Attenuation.z * len * len));

    col = colD * colA;
    
    return float4(col, col, col, 1.0f);

}