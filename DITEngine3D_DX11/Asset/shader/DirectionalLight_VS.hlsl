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

    //光の方向から頂点の明るさを決定
    //float d = -dot(Light_Sun.Direction.xyz, worldNormal.xyz);
    //d = saturate(d);
    
    //環境マップに必要な頂点までの視点ベクトル
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