
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

	float d = - dot(Light.Direction.xyz, worldNormal.xyz);
	d = saturate(d);


	Out.Diffuse = In.Diffuse * Material.Diffuse * d * Light.Diffuse;
	Out.Diffuse += In.Diffuse * Material.Ambient * Light.Ambient;
	Out.Diffuse += Material.Emission;
	Out.Diffuse.a = In.Diffuse.a * Material.Diffuse.a;


	Out.Diffuse.xyz = In.Diffuse.xyz * Material.Diffuse.xyz * d * Light.Diffuse.xyz;
	Out.Diffuse.xyz += In.Diffuse.xyz * Material.Ambient.xyz * Light.Ambient.xyz;
	Out.Diffuse.xyz += Material.Emission.xyz;
	Out.Diffuse.a = In.Diffuse.a* Material.Diffuse.a;

	Out.Position = mul( In.Position, wvp );
	Out.TexCoord = In.TexCoord;

}

