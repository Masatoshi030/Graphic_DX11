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
    
    Color = Material.Diffuse * CubeMap.SampleLevel(g_SamplerState, float2(coordX, coordY) * float2(0.5f, -0.5f) + 0.5f, -10.0);
    
    
    //== 平均化フィルター適用 ==//
    
    ////１ピクセル当たりのUV値
    //float2 PixelSize = float2(1.0 / EnvironmentMap_Info.ImageSize.x, 1.0 / EnvironmentMap_Info.ImageSize.y);
    //
    //float2 filter[9] =
    //{
    //    float2(-PixelSize.x, -PixelSize.y),
    //    float2(0, -PixelSize.y),
    //    float2(PixelSize.x, -PixelSize.y),
    //    float2(-PixelSize.x, 0),
    //    float2(0, 0),
    //    float2(PixelSize.x, 0),
    //    float2(-PixelSize.x, PixelSize.y),
    //    float2(0, PixelSize.y),
    //    float2(PixelSize.x, PixelSize.y)
    //};
    //
    //for (int filter_i = 0; filter_i < 9; filter_i++)
    //{
    //    //物体のテクスチャを適用
    //    Color += Material.Diffuse * CubeMap.Sample(g_SamplerState, float2(coordX + filter[filter_i].x, coordY + filter[filter_i].y) * float2(0.5f, -0.5f) + 0.5f);
    //}
    //
    //Color = float4((Color / 9.0).rgb, 1.0);
    
    
    //== スペキュラー適用 ==//
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