#include "common.hlsl"

//環境画像
TextureCube g_Texture : register(t0);
SamplerState g_SamplerState : register(s0);

float FrenselEquations(float reflectionCoef, float3 H, float3 V)
{
    return (reflectionCoef + (1.0f - reflectionCoef) * pow(1.0 - saturate(dot(V, H)), 5.0));
}

float3 ReflectionFrensel(float4 posw, float4 norw, float4 eye, float eta)
{
    float3 N = norw;
    float3 I = normalize(posw.xyz - eye.xyz);
    float3 R = reflect(I, N);
    float3 T = refract(I, N, eta);
    float fresnel = FrenselEquations(pow(eta - 1 / eta + 1, 2), N, I);

    float3 reflecColor = g_Texture.Sample(g_SamplerState, R);
    float3 refracColor = g_Texture.Sample(g_SamplerState, T);

    float3 col = lerp(refracColor, reflecColor, fresnel);

    return col;
}

float4 ps_main(PS_IN input) : SV_Target
{
    float4 Color;
    
    //環境テクスチャ適用
    Color = float4(ReflectionFrensel(input.posw, input.norw, Eye_Info.EyePosition, 1.0f), 1.0f);
    
    float3 l;
    float3 n;
    float3 r;
    float3 v;
    float i;
    
    l = normalize(Light_Point.Position.xyz - input.posw.xyz);
    n = normalize(input.norw.xyz);
    r = 2.0 * n * dot(n, l) - l;
    v = normalize(Eye_Info.EyePosition.xyz - input.posw.xyz);
    i = pow(saturate(dot(r, v)), Material.Shininess);
    
    Color += float4(i * Material.Specular.xyz * Light_Point.LightColor.xyz, 1.0f);
    
    
    return Color;

}