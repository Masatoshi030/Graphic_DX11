


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
	float4 Ambient;			//����
	float4 Diffuse;			//�g�U�@�S�̖̂��邳
	float4 Specular;		//���ʔ��ˌ�
	float4 Emission;		//����
	float Shininess;		//
	bool TextureEnable;
	float2 Dummy;
};

cbuffer MaterialBuffer : register(b3)
{
	MATERIAL Material;
}



// ���s�����iDirectional Light�j
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


// �_�����iPoint Light�j
struct LIGHT_POINT
{
    float4 Position;		//�����̍��W
    float4 Attenuation;		//����
    float4 LightColor;		//�_�����̐F
};

cbuffer PointLightBuffer : register(b5)
{
    LIGHT_POINT Light_Point;
}


struct EYE_INFO
{
    float4 EyePosition; //���_�̍��W
};

cbuffer EyeInfo : register(b6)
{
    EYE_INFO Eye_Info;
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
    float3 ViewVector	: TEXCOORD1;
};