#include "common.hlsl"

//�e�N�X�`��
Texture2D g_environmentMap : register(t0);
Texture2D g_albedo_Texture : register(t1);
Texture2D g_normalMap_Texture : register(t2);
Texture2D g_metallicSmoothMap_Texture : register(t3);

SamplerState g_SamplerState : register(s0);

//���
float sqr(float x)
{
    return x * x;
}

float CalcDiffuseFromFresnel_Disney(float3 N, float3 L, float3 V)
{
    
    //�����Ɍ������x�N�g���Ǝ����Ɍ������x�N�g���̃n�[�t�x�N�g�������߂�
    float3 H = normalize(L + V);
    
    float energyBias = lerp(0.0, 0.5, Disney_Material.Roughness.x);
    
    float energyFactor = lerp(1.0, 1.0 / 1.51, Disney_Material.Roughness.x);

    //�����Ɍ������x�N�g���ƃn�[�t�x�N�g�����ǂꂾ�����Ă��邩��
    float dotLH = saturate(dot(L, H));
    
    //�����Ɍ������x�N�g���ƃn�[�t�x�N�g���A�������s�ɓ��˂������̊g�U���˗ʂ����߂�
    float Fd90 = energyBias + 2.0 * dotLH * dotLH * Disney_Material.Roughness.x;
    
    //�@���ƌ����Ɍ������x�N�g��W�𗘗p���Ċg�U���˗������߂�
    float dotNL = saturate(dot(N, L));
    float FL = (1 + (Fd90 - 1) * pow(1 - dotNL, 5));

    //�@���Ǝ��_�Ɍ������x�N�g���𗘗p���Ċg�U���˗������߂�
    
    float dotNV = saturate(dot(N, V));
    float FV = (1 + (Fd90 - 1) * pow(1 - dotNV, 5));
    
    //�@���ƌ����ւ̕����Ɉˑ�����g�U���˗��ƁA�@���Ǝ��_�x�N�g���Ɉˑ�����g�U���˗�����Z����
    //�ŏI�I�Ȋg�U���˗������߂Ă���BPIE�ŏ��Z���Ă���̂͐��K���̂���
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
    
    // �o�͐F��������
    float4 returnColor = 0.0;
    
    
    //== �x�N�g�� ==//
    
    //���C�g�Ɍ������x�N�g��
    float3 L = -Light_Sun.Direction.xyz;
    
    //�r���[�Ɍ������x�N�g��
    float3 V = normalize(Eye_Info.EyePosition.xyz - input.posw.xyz);
    
    //�@���̃x�N�g��
    float3 N = normalize(input.norw.xyz);
    
    // ���C�g�Ɍ������x�N�g���Ǝ����Ɍ������x�N�g���̃n�[�t�x�N�g�������߂�
    float3 H = normalize(L + V);
    
    //�n�[�t�x�N�g���Ɗe�x�N�g���̋߂�
    float NdotH = saturate(dot(N, H));
    float VdotH = saturate(dot(V, H));
    float LdotH = saturate(dot(L, H));
    float NdotL = saturate(dot(N, L));
    float NdotV = saturate(dot(N, V));
    
    //Tangent��Binormal
    float3 tangent = normalize(cross(N, float3(0.0001, 1, 0.0001)));
    float3 binormal = normalize(cross(tangent, N));
    
    
    //== �e��}�b�v���T���v�����O ==//
    
    // �A���x�h�i�g�U���ˌ��j
    //float4 albedoColor = g_albedo_Texture.Sample(g_SamplerState, input.TexCoord);
    float4 albedoColor = Disney_Material.BaseColor;
    
    // �X�y�L�����[���A���x�h�Ɠ����F�ɐݒ�
    float3 specularColor = albedoColor;
    
    //�����x
    //float metallic = g_metallicSmoothMap_Texture.Sample(g_SamplerState, input.TexCoord).r;
    float metallic = Disney_Material.Metallic.x;
    
    //���炩��
    //float smooth = g_metallicSmoothMap_Texture.Sample(g_SamplerState, input.TexCoord).a;
    float smooth = 1 - Disney_Material.Roughness.x;
   
    
    
    //== �g�U����BRDF ==//
    
    //�t���l�����˂��l�������g�U���˂��v�Z�@���̋������l��
    float diffuseFromFrensnel = CalcDiffuseFromFresnel_Disney(N, L, V);
    
    //���^���b�N�ƃ��t�l�X����g�U���˂̉e���x���v�Z
    diffuseFromFrensnel *= max(Disney_Material.Roughness.x, 1 - Disney_Material.Metallic.x);
    
    //���K��Lambert�g�U���˂����߂�
    float3 lambertDiffuse = Light_Sun.Diffuse * NdotL / PIE;
    
    //�ŏI�I�Ȋg�U���ˌ����v�Z
    float3 diffuse = diffuseFromFrensnel * lambertDiffuse;
    
    
    //== ���ʔ���BRDF ==//
    
    //Specular
    
    //���ʔ��˓x
    float3 F0 = lerp(0.15, albedoColor, metallic);
    
    float FH = SchlickFresnel(F0, LdotH);
    
    //�ٕ������˂̕����Ƌ������v�Z
    float aspect = sqrt(1 - Disney_Material.Anisotropic.x * 0.9);
    float ax = max(0.001, sqr(Disney_Material.Roughness.x) / aspect);
    float ay = max(0.001, sqr(Disney_Material.Roughness.x) * aspect);
    
    //D��
    float Ds = GTR2_aniso(NdotH, dot(H, tangent), dot(H, binormal), ax, ay);
    
    //F��
    float Fs = lerp(0.04, 1, FH);
    
    //G��
    float roughg = sqr(Disney_Material.Roughness.x * 0.5 + 0.5);
    float Gs = smithG_GGX(NdotL, roughg) * smithG_GGX(NdotV, roughg);
    
    //���^���b�N�̒l�ŃX�y�L�����[�F���x�[�X�J���[�ɋ߂Â���
    specularColor = lerp(float3(1, 1, 1), albedoColor.rgb, metallic);
    
    //�X�y�L�����[�̌v�Z����
    float specular = Gs * Fs * Ds;
    
    
    //ClearCoat
    
    //D��
    float Dc = GTR1(NdotH, lerp(0.1, 0.001, Disney_Material.ClearCoat.x));
    
    //F��
    float Fc = lerp(0.04, 1, FH);
    
    //G��
    float Gc = smithG_GGX(NdotL, 0.25) * smithG_GGX(NdotV, 0.25);
    
    //�N���A�R�[�g�̌v�Z����
    float clearCoat = Gc * Fc * Dc * Disney_Material.ClearCoatGloss.x;
    
    
    //== ���� ==//
    
    //�e�v�Z���ʂ�����
    returnColor.rgb = diffuse * Light_Sun.Intensity.x * albedoColor.rgb + specular * specularColor + clearCoat;
    
    //�����ƃA���x�h�̓K�p
    returnColor.rgb += Light_Sun.Ambient.rgb * albedoColor.rgb;
    
    
    //== ���e�N�X�`���K�p ==//
    
    // �ڂ����̓x���������t�l�X����v�Z
    float blurAmount = Disney_Material.Roughness.x;

    // ���}�b�v����̔��˃x�N�g�����v�Z
    float3 reflectedDir = reflect(-V, N);

    // �ڂ�����K�p
    reflectedDir = lerp(reflectedDir, normalize(N), blurAmount);
    
    //���˃x�N�g�����狅��ɋ���
    float coordX = atan2(reflectedDir.x, reflectedDir.z) / PIE;
    float coordY = asin(reflectedDir.y) / (PIE / 2.0f);
    
    //UV�̌v�Z
    float3 environmentMap_UV = reflectedDir;
    
    float2 enviromentMap_SphereUV = float2(coordX, coordY) * float2(0.5f, -0.5f) + 0.5f;
    
    //���}�b�v�̃J���[
    float4 environmentColor = 0;
    
    //���}�b�v���T���v�����O
    environmentColor = g_environmentMap.Sample(g_SamplerState, enviromentMap_SphereUV);
    
    //���}�b�v������
    returnColor *= ((environmentColor - 1.0) * max(Disney_Material.Metallic.x + 0.1, 0)) + 1.0;
    
    //BRDS�̖������ɂ�铧���x�̏C��
    returnColor.a = 1.0;
    
    return returnColor;
}