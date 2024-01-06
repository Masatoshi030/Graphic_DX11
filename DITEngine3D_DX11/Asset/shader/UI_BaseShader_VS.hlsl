
#include "common.hlsl"


void main(in VS_IN In, out PS_IN Out)
{
    matrix wvp;
    wvp = mul(World, View);
    wvp = mul(wvp, Projection);
    
    //�A�t�B���ϊ�
    float4 AffineResult = mul(float4(In.Position.x, In.Position.y, 0, 1), AffineMatrix);
    
    //�A�t�B���ϊ��̌��ʂ����W�ɔ��f
    In.Position = float4(AffineResult.xy, In.Position.zw);

    //2D��p�s��Ŕ|������ʍ��W�ɂ���
    Out.Position = mul(In.Position, wvp);
    
    //��ʂ̒��������_�ɂ���
    Out.Position += float4(1.0, -1.0, 0.0, 0.0);
    
    Out.TexCoord = In.TexCoord;
    Out.Diffuse = In.Diffuse * Material.Diffuse;
}

