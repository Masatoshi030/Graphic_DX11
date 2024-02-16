#include "common.hlsl"


void main(in VS_IN In, out PS_IN Out)
{
    matrix wvp;
    wvp = mul(World, View);
    wvp = mul(wvp, Projection);
	
    float4 worldNormal, normal;
    normal = float4(In.Normal.xyz, 0.0);
    worldNormal = mul(normal, World);
    worldNormal = normalize(worldNormal);

    //���̕������璸�_�̖��邳������
    //float d = -dot(Light_Sun.Direction.xyz, worldNormal.xyz);
    //d = saturate(d);
    
    //���}�b�v�ɕK�v�Ȓ��_�܂ł̎��_�x�N�g��
    Out.posw = mul(In.Position, World);
    Out.ViewVector = normalize(Out.posw - Eye_Info.EyePosition);
    Out.norw = worldNormal;


    //Out.Diffuse = In.Diffuse * d * Light_Sun.Diffuse;
    Out.Diffuse = In.Diffuse;
    Out.Diffuse += In.Diffuse * Light_Sun.Ambient;
    Out.Diffuse.a = In.Diffuse.a * Disney_Material.BaseColor.a;


    Out.Position = mul(In.Position, wvp);
    
    Out.TexCoord = In.TexCoord;

}