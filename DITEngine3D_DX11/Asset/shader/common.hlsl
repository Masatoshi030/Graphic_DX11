
#define PIE 3.1415926f


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
	float4 Ambient;			//環境光
	float4 Diffuse;			//拡散　全体の明るさ
	float4 Specular;		//鏡面反射光
	float4 Emission;		//発光
	float Shininess;		//
	bool TextureEnable;
	float2 Dummy;
    float4 Metallic;
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
    float4 LightColor;		//点光源の色
};

cbuffer PointLightBuffer : register(b5)
{
    LIGHT_POINT Light_Point;
}


struct EYE_INFO
{
    float4 EyePosition; //視点の座標
};

cbuffer EyeInfo : register(b6)
{
    EYE_INFO Eye_Info;
}


struct ENVIRONMENTMAP_INFO
{
    float4 ImageSize; //環境マップの解像度
};

cbuffer EnvironmentMapInfo : register(b7)
{
    ENVIRONMENTMAP_INFO EnvironmentMap_Info;
};


cbuffer UI_Info : register(b8)
{
    matrix AffineMatrix;	//UIのトランスフォームを決めるアフィン変換行列
};


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
    float4 norw			: NORMAL;
    float3 ViewVector	: TEXCOORD1;
};