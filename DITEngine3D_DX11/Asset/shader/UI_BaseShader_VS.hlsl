
#include "common.hlsl"


void main(in VS_IN In, out PS_IN Out)
{
    matrix wvp;
    wvp = mul(World, View);
    wvp = mul(wvp, Projection);
    
    //アフィン変換
    float4 AffineResult = mul(float4(In.Position.x, In.Position.y, 0, 1), AffineMatrix);
    
    //アフィン変換の結果を座標に反映
    In.Position = float4(AffineResult.xy, In.Position.zw);

    //2D専用行列で板ポリを画面座標にする
    Out.Position = mul(In.Position, wvp);
    
    //画面の中央を原点にする
    Out.Position += float4(1.0, -1.0, 0.0, 0.0);
    
    Out.TexCoord = In.TexCoord;
    Out.Diffuse = In.Diffuse * Material.Diffuse;
}

