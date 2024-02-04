#include "common.hlsl"

//テクスチャ
Texture2D g_environmentMap : register(t0);
Texture2D g_albedo_Texture : register(t1);
Texture2D g_normalMap_Texture : register(t2);
Texture2D g_metallicSmoothMap_Texture : register(t3);

SamplerState g_SamplerState : register(s0);

//二乗
float sqr(float x)
{
    return x * x;
}

float CalcDiffuseFromFresnel_Disney(float3 N, float3 L, float3 V)
{
    
    //光源に向かうベクトルと視線に向かうベクトルのハーフベクトルを求める
    float3 H = normalize(L + V);
    
    float energyBias = lerp(0.0, 0.5, Disney_Material.Roughness.x);
    
    float energyFactor = lerp(1.0, 1.0 / 1.51, Disney_Material.Roughness.x);

    //光源に向かうベクトルとハーフベクトルがどれだけ似ているかを
    float dotLH = saturate(dot(L, H));
    
    //光源に向かうベクトルとハーフベクトル、光が平行に入射した時の拡散反射量を求める
    float Fd90 = energyBias + 2.0 * dotLH * dotLH * Disney_Material.Roughness.x;
    
    //法線と光源に向かうベクトルWを利用して拡散反射率を求める
    float dotNL = saturate(dot(N, L));
    float FL = (1 + (Fd90 - 1) * pow(1 - dotNL, 5));

    //法線と視点に向かうベクトルを利用して拡散反射率を求める
    
    float dotNV = saturate(dot(N, V));
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
    return 1 / (PIE * ax * ay * sqr(sqr(HdotX / ax) + sqr(HdotY / ay) + NdotH * NdotH));
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
    //float4 albedoColor = g_albedo_Texture.Sample(g_SamplerState, input.TexCoord);
    float4 albedoColor = Disney_Material.BaseColor;
    
    // スペキュラーをアルベドと同じ色に設定
    float3 specularColor = albedoColor;
    
    //金属度
    //float metallic = g_metallicSmoothMap_Texture.Sample(g_SamplerState, input.TexCoord).r;
    float metallic = Disney_Material.Metallic.x;
    
    //滑らかさ
    //float smooth = g_metallicSmoothMap_Texture.Sample(g_SamplerState, input.TexCoord).a;
    float smooth = 1 - Disney_Material.Roughness.x;
   
    
    
    //== 拡散反射BRDF ==//
    
    //フレネル反射を考慮した拡散反射を計算　光の強さも考慮
    float diffuseFromFrensnel = CalcDiffuseFromFresnel_Disney(N, L, V);
    
    //メタリックとラフネスから拡散反射の影響度を計算
    diffuseFromFrensnel *= max(Disney_Material.Roughness.x, 1 - Disney_Material.Metallic.x);
    
    //正規化Lambert拡散反射を求める
    float3 lambertDiffuse = Light_Sun.Diffuse * NdotL / PIE;
    
    //最終的な拡散反射光を計算
    float3 diffuse = diffuseFromFrensnel * lambertDiffuse;
    
    
    //== 鏡面反射BRDF ==//
    
    //Specular
    
    //鏡面反射度
    float3 F0 = lerp(0.15, albedoColor, metallic);
    
    float FH = SchlickFresnel(F0, LdotH);
    
    //異方性反射の方向と強さを計算
    float aspect = sqrt(1 - Disney_Material.Anisotropic.x * 0.9);
    float ax = max(0.001, sqr(Disney_Material.Roughness.x) / aspect);
    float ay = max(0.001, sqr(Disney_Material.Roughness.x) * aspect);
    
    //D項
    float Ds = GTR2_aniso(NdotH, dot(H, tangent), dot(H, binormal), ax, ay);
    
    //F項
    float Fs = lerp(0.04, 1, FH);
    
    //G項
    float roughg = sqr(Disney_Material.Roughness.x * 0.5 + 0.5);
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
    
    
    //== 環境テクスチャ適用 ==//
    
    // ぼかしの度合いをラフネスから計算
    float blurAmount = Disney_Material.Roughness.x;

    // 環境マップからの反射ベクトルを計算
    float3 reflectedDir = reflect(-V, N);

    // ぼかしを適用
    reflectedDir = lerp(reflectedDir, normalize(N), blurAmount);
    
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
    returnColor *= ((environmentColor - 1.0) * max(Disney_Material.Metallic.x + 0.1, 0)) + 1.0;
    
    //BRDSの未実装による透明度の修正
    returnColor.a = 1.0;
    
    return returnColor;
}