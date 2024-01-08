#include "common.hlsl"

//���摜
Texture2D CubeMap : register(t0);
Texture2D Albedo_Texture : register(t1);
SamplerState g_SamplerState : register(s0);

float4 ps_main(PS_IN input) : SV_Target
{
    float4 Color;
    
    //== ���e�N�X�`���K�p ==//
    
    // ���_����s�N�Z���܂ł̃x�N�g���Ɩ@���x�N�g�����甽�˃x�N�g�����v�Z
    float3 dir = reflect(input.ViewVector, input.norw.xyz);
    
    //���˃x�N�g�����狅��ɋ���
    float coordX = atan2(dir.x, dir.z) / PIE;
    float coordY = asin(dir.y) / (PIE / 2.0f);
    
    //���e�N�X�`����K�p
    Color = (CubeMap.SampleLevel(g_SamplerState, float2(coordX, coordY) * float2(0.5f, -0.5f) + 0.5f, -10.0));
    
    //���^���b�N�̓x����0�`1�̃R���g���X�g�𒲐�
    Color = ((Color - 1.0) * max(Material.Metallic.x + 0.1, 0)) + 1.0;
    
    //�x�[�X�̐F������
    Color *= Material.Diffuse;
    
    Color *= saturate(input.Diffuse + Material.Metallic.x);
    
    
    //== �X�y�L�����[�K�p ==//
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