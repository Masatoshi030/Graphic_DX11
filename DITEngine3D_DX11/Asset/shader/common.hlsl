
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




struct MATERIAL
{
	float4 Ambient;			//����
	float4 Diffuse;			//�g�U�@�S�̖̂��邳
	float4 Specular;		//���ʔ��ˌ�
	float4 Emission;		//����
	float Shininess;		//
	bool TextureEnable;
	float2 Dummy;
    float4 Metallic;
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
    float4 Intensity;
};

cbuffer SunLightBuffer : register(b4)
{
	LIGHT_SUN Light_Sun;
}

#define Sun


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


struct ENVIRONMENTMAP_INFO
{
    float4 ImageSize; //���}�b�v�̉𑜓x
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

struct DISNEY_MATERIAL
{
    //�x�[�X�J���[
    float4 BaseColor;
    //���^���b�N
    float4 Metallic;
    //�T�u�T�[�t�F�X
    float4 SubSurface;
    //�X�y�L�����[���x
    float4 Specular;
    //�X�y�L�����[�`���g
    float4 SpecularTint;
    //���t�l�X
    float4 Roughness;
    //�ٕ�������
    float4 Anisotropic;
    //�ٕ������ˁ@X
    float4 Anisotropic_X;
    //�ٕ�������Y
    float4 Anisotropic_Y;
    //�V�[��
    float4 Sheen;
    //�V�[���`  ���g
    float4 SheenTint;
    //�N���A�R�[�g���x
    float4 ClearCoat;
    //�N���A�R�[�g���򋭓x
    float4 ClearCoatGloss;
};

cbuffer CB_Disney_Material : register(b10)
{
    DISNEY_MATERIAL Disney_Material;
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