#include "common.hlsl"

Texture2D g_Texture : register(t1);
SamplerState g_SamplerState : register(s0);

float4 ps_main(PS_IN input) : SV_Target
{
    float4 Color;
    
    float3 dir;
    float len;
    float colD;
    float colA;
    float col;
    
    //�_�����̕���
    dir = Light_Point.Position.xyz - input.posw.xyz;
    
    //�_�����̋���
    len = length(dir);
    
    //�_�����̕����𐳋K��
    dir = dir / len;
    
    //�g�U
    colD = saturate(dot(normalize(input.norw.xyz), dir));
    
    //����
    colA = saturate(1.0f / (Light_Point.Attenuation.x + Light_Point.Attenuation.y * len + Light_Point.Attenuation.z * len * len));

    col = colD * colA;
    
    Color = float4(col, col, col, 1.0f);
    
    if (Material.TextureEnable)
    {
        Color *= g_Texture.Sample(g_SamplerState, input.TexCoord);
    }
    
    Color *= input.Diffuse;
    
    Color += Light_Sun.Ambient;
    
    return Color;

}