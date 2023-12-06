


cbuffer WorldBuffer : register(b0)
{
	matrix World;
}
cbuffer ViewBuffer : register(b1)
{
	matrix View;
}
cbuffer ProjectionBuffer : register(b2)
{
	matrix Projection;
}




struct MATERIAL
{
	float4 Ambient;
	float4 Diffuse;
	float4 Specular;
	float4 Emission;
	float Shininess;
	bool TextureEnable;
	float2 Dummy;
};

cbuffer MaterialBuffer : register(b3)
{
	MATERIAL Material;
}



// 平行光源（Directional Light）
struct LIGHT_SUN
{
	bool Enable;
	bool3 Dummy;
	float4 Direction;
	float4 Diffuse;
	float4 Ambient;
};

cbuffer SunLightBuffer : register(b4)
{
	LIGHT_SUN Light_Sun;
}


// 点光源（Point Light）
struct LIGHT_POINT
{
    float4 Position;		//光源の座標
    float4 Attenuation;		//減衰
};

cbuffer PointLightBuffer : register(b5)
{
    LIGHT_POINT Light_Point;
}





struct VS_IN
{
	float4 Position		: POSITION0;
	float4 Normal		: NORMAL0;
	float4 Diffuse		: COLOR0;
	float2 TexCoord		: TEXCOORD0;
};


struct PS_IN
{
	float4 Position		: SV_POSITION;
	float4 Diffuse		: COLOR0;
	float2 TexCoord		: TEXCOORD0;
    float4 posw			: POSITION0;
    float4 norw			: NORMAL0;
};