#include "common.hlsl"

//環境画像
Texture2D CubeMap : register(t0);
Texture2D Albedo_Texture : register(t1);
SamplerState g_SamplerState : register(s0);

float4 ps_main(PS_IN input) : SV_Target
{
    float4 Color;
    
    //== 環境テクスチャ適用 ==//
    
    // 視点からピクセルまでのベクトルと法線ベクトルから反射ベクトルを計算
    float3 dir = reflect(input.ViewVector, input.norw.xyz);
    
    //反射ベクトルから球状に強制
    float coordX = atan2(dir.x, dir.z) / PIE;
    float coordY = asin(dir.y) / (PIE / 2.0f);
    
    //環境テクスチャを適用
    Color = (CubeMap.SampleLevel(g_SamplerState, float2(coordX, coordY) * float2(0.5f, -0.5f) + 0.5f, -10.0));
    
    //メタリックの度合で0～1のコントラストを調節
    Color = ((Color - 1.0) * max(Material.Metallic.x + 0.1, 0)) + 1.0;
    
    //ベースの色を入れる
    Color *= Material.Diffuse;
    
    Color *= saturate(input.Diffuse + Material.Metallic.x);
    
    
    //== スペキュラー適用 ==//
    float3 l;
    float3 n;
    float3 r;
    float3 v;
    float i;
    
    l = normalize(-Light_Sun.Direction.xyz);
    n = normalize(input.norw.xyz);
    r = 2.0 * n * dot(n, l) - l;
    v = normalize(Eye_Info.EyePosition.xyz - input.posw.xyz);
    i = pow(saturate(dot(r, v)), Material.Shininess.x * 50);
    
    Color += float4(i * Light_Sun.Diffuse.xyz * Material.Shininess, 1.0f);
    
    return Color;

}