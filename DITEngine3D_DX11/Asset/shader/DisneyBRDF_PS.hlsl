#include "common.hlsl"

//テクスチャ
Texture2D g_environmentMap : register(t0);
Texture2D g_albedo_Texture : register(t1);
Texture2D g_normalMap_Texture : register(t2);
Texture2D g_metallicMap_Texture : register(t3);

SamplerState g_SamplerState : register(s0);

//二乗
float sqr(float x)
{
    return x * x;
}

float CalcDiffuseFromFresnel_Disney(float3 N, float3 L, float3 V, float3 H, float dotLH, float dotNL, float dotNV, float roughness)
{
    
    float energyBias = lerp(0.0, 0.5, roughness);
    
    float energyFactor = lerp(1.0, 1.0 / 1.51, roughness);
    
    //光源に向かうベクトルとハーフベクトル、光が平行に入射した時の拡散反射量を求める
    float Fd90 = energyBias + 2.0 * dotLH * dotLH * roughness;
    
    //法線と光源に向かうベクトルWを利用して拡散反射率を求める
    float FL = (1 + (Fd90 - 1) * pow(1 - dotNL, 5));

    //法線と視点に向かうベクトルを利用して拡散反射率を求める
    float FV = (1 + (Fd90 - 1) * pow(1 - dotNV, 5));
    
    //法線と光源への方向に依存する拡散反射率と、法線と視点ベクトルに依存する拡散反射率を乗算して
    //最終的な拡散反射率を求めている。PIEで除算しているのは正規化のため
    return (FL * FV * energyFactor);

}

float smithG_GGX(float Ndotv, float alphaG)
{
    float a = alphaG * alphaG;
    float b = Ndotv * Ndotv;
    return 1 / (Ndotv + sqrt(a + b - a * b));
}

float3 SchlickFresnel(float3 F0, float3 H)
{
    return F0 + (1.0 - F0) * pow(1.0 - dot(H, normalize(float3(1.0, 1.0, 1.0))), 5.0);
}

float GTR1(float NdotH, float a)
{
    if (a >= 1)
    {
        return 1 / PIE;
    }
    float a2 = a * a;
    float t = 1 + (a2 - 1) * NdotH * NdotH;
    return (a2 - 1) / (PIE * log(a2) * t);
}

float GTR2_aniso(float NdotH, float HdotX, float HdotY, float ax, float ay)
{
    float HdotX_normalized = abs(HdotX);
    float HdotY_normalized = abs(HdotY);
    return 1 / (PIE * ax * ay * sqr(sqr(HdotX_normalized / ax) + sqr(HdotY_normalized / ay) + NdotH * NdotH));
}

float4 ps_main(PS_IN input) : SV_Target
{
    
    // 出力色を初期化
    float4 returnColor = 0.0;
    
    
    //== ベクトル ==//
    
    //ライトに向かうベクトル
    float3 L = -Light_Sun.Direction.xyz;
    
    //ビューに向かうベクトル
    float3 V = normalize(Eye_Info.EyePosition.xyz - input.posw.xyz);
    
    //法線マップ
    float3 normalmap = input.norw.xyz;
    
    if (saturate(Disney_Material.TextureEnable.y) != 0.0)
    {
        normalmap = normalize(g_normalMap_Texture.Sample(g_SamplerState, input.TexCoord));
        input.norw.xyz = normalize(input.norw.xyz + normalmap * Disney_Material.NormalMap_Intensity.x);
    }
    
    //法線のベクトル
    float3 N = normalize(input.norw.xyz);
    
    // ライトに向かうベクトルと視線に向かうベクトルのハーフベクトルを求める
    float3 H = normalize(L + V);
    
    //ハーフベクトルと各ベクトルの近さ
    float NdotH = saturate(dot(N, H));
    float VdotH = saturate(dot(V, H));
    float LdotH = saturate(dot(L, H));
    float NdotL = saturate(dot(N, L));
    float NdotV = saturate(dot(N, V));
    
    //TangentとBinormal
    float3 tangent = normalize(cross(N, float3(0.0001, 1, 0.0001)));
    float3 binormal = normalize(cross(tangent, N));
    
    
    //== 各種マップをサンプリング ==//
    
    // アルベド（拡散反射光）

    float4 albedoColor = 1;
    
    //テクスチャが有効であれば適用
    albedoColor = saturate(g_albedo_Texture.Sample(g_SamplerState, input.TexCoord) + (1 - saturate(Disney_Material.TextureEnable.x)));
    
    albedoColor *= Disney_Material.BaseColor;
    
    // スペキュラーをアルベドと同じ色に設定
    float3 specularColor = albedoColor;
    
    //金属度
    float metallic = Disney_Material.Metallic.x;
    float roughness = Disney_Material.Roughness.x;
    if (saturate(Disney_Material.TextureEnable.z) != 0.0)
    {
        metallic = 1 - g_metallicMap_Texture.Sample(g_SamplerState, input.TexCoord).r;
        roughness = metallic;
    }
        //float metallic = Disney_Material.Metallic.x;
    
    //滑らかさ
    //float smooth = g_metallicSmoothMap_Texture.Sample(g_SamplerState, input.TexCoord).a;
    
    float smooth = 1 - roughness;
    
    
    //== 拡散反射BRDF ==//
    
    //フレネル反射を考慮した拡散反射を計算　光の強さも考慮
    float diffuseFromFrensnel = CalcDiffuseFromFresnel_Disney(N, L, V, H, LdotH, NdotL, NdotV, roughness);
    
    //メタリックとラフネスから拡散反射の影響度を計算
    diffuseFromFrensnel *= max(roughness, 1 - metallic);
    
    //正規化Lambert拡散反射を求める
    float3 lambertDiffuse = Light_Sun.Diffuse * NdotL / PIE;
    
    //最終的な拡散反射光を計算
    float3 diffuse = diffuseFromFrensnel * lambertDiffuse;
    
    
    //== 鏡面反射BRDF ==//
    
    
    //== 環境テクスチャ適用 ==//

    // 環境マップからの反射ベクトルを計算
    float3 reflectedDir = reflect(-V, N);
    
    //反射ベクトルから球状に強制
    float coordX = atan2(reflectedDir.x, reflectedDir.z) / PIE;
    float coordY = asin(reflectedDir.y) / (PIE / 2.0f);
    
    //UVの計算
    float3 environmentMap_UV = reflectedDir;
    
    float2 enviromentMap_SphereUV = float2(coordX, coordY) * float2(0.5f, -0.5f) + 0.5f;
    
    //環境マップのカラー
    float4 environmentColor = 0;
    
    //環境マップをサンプリング
    environmentColor = g_environmentMap.Sample(g_SamplerState, enviromentMap_SphereUV);
    
    //環境マップを合成
    albedoColor *= ((environmentColor - 1.0) * max(metallic + 0.1, 0)) + 1.0;
    
    
    
    
    
    //Specular
    
    //鏡面反射度
    float3 F0 = lerp(0.15, albedoColor, metallic);
    
    float FH = SchlickFresnel(F0, LdotH);
    
    //異方性反射の方向と強さを計算
    float aspect = sqrt(1 - Disney_Material.Anisotropic.x * 0.9);
    float ax = max(0.001, sqr(roughness) / aspect);
    float ay = max(0.001, sqr(roughness) * aspect);
    
    //D項
    float Ds = GTR2_aniso(NdotH, dot(H, tangent), dot(H, binormal), ax, ay);
    
    //F項
    float Fs = lerp(0.04, 1, FH);
    
    //G項
    float roughg = sqr(roughness * 0.5 + 0.5);
    float Gs = smithG_GGX(NdotL, roughg) * smithG_GGX(NdotV, roughg);
    
    //メタリックの値でスペキュラー色をベースカラーに近づける
    specularColor = lerp(float3(1, 1, 1), albedoColor.rgb, metallic);
    
    //スペキュラーの計算結果
    float specular = Gs * Fs * Ds;
    
    
    //ClearCoat
    
    //D項
    float Dc = GTR1(NdotH, lerp(0.1, 0.001, Disney_Material.ClearCoat.x));
    
    //F項
    float Fc = lerp(0.04, 1, FH);
    
    //G項
    float Gc = smithG_GGX(NdotL, 0.25) * smithG_GGX(NdotV, 0.25);
    
    //クリアコートの計算結果
    float clearCoat = Gc * Fc * Dc * Disney_Material.ClearCoatGloss.x;
    
    
    //== 合成 ==//
    
    //各計算結果を合成
    returnColor.rgb = diffuse * Light_Sun.Intensity.x * albedoColor.rgb + specular * specularColor + clearCoat;
    
    //環境光とアルベドの適用
    returnColor.rgb += Light_Sun.Ambient.rgb * albedoColor.rgb;
    
   
    //BRDSの未実装による透明度の修正
    returnColor.a = 1.0;
    
    
    //== 距離フォグ ==//
    
    returnColor = lerp(returnColor, Eye_Info.DistanceFog_Color, distance(Eye_Info.EyePosition.xyz, input.posw.xyz) * Eye_Info.DistanceFog_Distance.x);
    
    return returnColor;
}