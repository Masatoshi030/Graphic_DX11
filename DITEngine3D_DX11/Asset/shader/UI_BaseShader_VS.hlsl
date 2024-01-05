
#include "common.hlsl"


void main(in VS_IN In, out PS_IN Out)
{

    matrix wvp;
    wvp = mul(World, View);
    wvp = mul(wvp, Projection);

    Out.Position = mul(In.Position, wvp);
    
    //アフィン変換
    //Out.Position = mul(Out.Position, AffineMatrix);
    
    Out.TexCoord = In.TexCoord;
    Out.Diffuse = In.Diffuse * Material.Diffuse;
}

