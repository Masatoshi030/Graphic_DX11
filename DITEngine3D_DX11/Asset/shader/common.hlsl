
#define PIE 3.14159265358979323846f


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


struct DISNEY_MATERIAL
{
    //ベースカラー
    float4 BaseColor;
    //メタリック
    float4 Metallic;
    //スペキュラー強度
    float4 Specular;
    //ラフネス
    float4 Roughness;
    //異方性反射
    float4 Anisotropic;
    //クリアコート強度
    float4 ClearCoat;
    //クリアコート光沢強度
    float4 ClearCoatGloss;
};

cbuffer CB_Disney_Material : register(b3)
{
    DISNEY_MATERIAL Disney_Material;
}



// 平行光源（Directional Light）
struct LIGHT_SUN
{
	bool Enable;
	bool3 Dummy;
	float4 Direction;
	float4 Diffuse;
	float4 Ambient;
    float4 Intensity;
};

cbuffer SunLightBuffer : register(b4)
{
	LIGHT_SUN Light_Sun;
}

#define Sun


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
    float4 DistanceFog_Color;   //距離フォグの色
    float4 DistanceFog_Distance;//距離フォグの距離
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
}


cbuffer UI_Info : register(b8)
{
    float4x4 AffineMatrix;
}

cbuffer SystemInfo : register(b9)
{
    float4 ScreenSize;
    float4 ScreenAspect;
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
    float4 norw			: NORMAL;
    float3 ViewVector	: TEXCOORD1;
};