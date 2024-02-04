#pragma once

//=============================================================//
//	Direct3D11���V���O���g���ŊǗ�����N���X
//=============================================================//

//Direct3D11
#include <d3d11.h>
#include <SimpleMath.h>
#include <DirectXMath.h>
#include "Application.h"

#pragma comment(lib, "directxtk.lib")
#pragma comment(lib, "d3d11.lib")

#define D3D DIRECT3D11::Get_Instance()

using namespace std;

//����}�N��
#define SAFE_RELEASE(_a) if(_a!=NULL){_a->Release();_a=NULL;}



//3D���_�f�[�^
struct VERTEX_3D
{
	DirectX::SimpleMath::Vector3 Position;
	DirectX::SimpleMath::Vector3 Normal;
	DirectX::SimpleMath::Color Diffuse;
	DirectX::SimpleMath::Vector2 TexCoord;
};


//�}�e���A��
struct MATERIAL
{
	DirectX::SimpleMath::Color Ambient;
	DirectX::SimpleMath::Color Diffuse;
	DirectX::SimpleMath::Color Specular;
	DirectX::SimpleMath::Color Emission;
	float Shininess;
	BOOL TextureEnable;
	float Dummy[2];
	DirectX::SimpleMath::Vector4 Metalic;
};


//���s����
struct LIGHT
{
	BOOL Enable;
	BOOL Dummy[3];
	DirectX::SimpleMath::Vector4 Direction;
	DirectX::SimpleMath::Color Diffuse;
	DirectX::SimpleMath::Color Ambient;
	DirectX::SimpleMath::Vector4 Intensity;
};


//�_����
struct LIGHT_POINT
{
	DirectX::SimpleMath::Vector4 Position;
	DirectX::SimpleMath::Vector4 Attenuation;
	DirectX::SimpleMath::Vector4 LightColor;
};


//���_���
struct EYE_INFO
{
	DirectX::SimpleMath::Vector4 EyePosition;	//���_�̍��W
};


//���}�b�v���
struct ENVIRONMENTMAP_INFO
{
	DirectX::SimpleMath::Vector4 ImageSize;
};


//�V�F�[�_�[�ɕK�v�ȃV�X�e�����
struct GPU_SYSTEM_INFO
{
	DirectX::SimpleMath::Vector4 ScreenSize;	//xy
	DirectX::SimpleMath::Vector4 ScreenAspect;	//x
};

//Disney BRDF �}�e���A��
struct DISNEY_MATERIAL
{
	//�x�[�X�J���[
	DirectX::SimpleMath::Color BaseColor;
	//���^���b�N
	DirectX::SimpleMath::Vector4 Metallic;
	//�X�y�L�����[���x
	DirectX::SimpleMath::Vector4 Specular;
	//���t�l�X
	DirectX::SimpleMath::Vector4 Roughness;
	//�ٕ�������
	DirectX::SimpleMath::Vector4 Anisotropic;
	//�N���A�R�[�g���x
	DirectX::SimpleMath::Vector4 ClearCoat;
	//�N���A�R�[�g���򋭓x
	DirectX::SimpleMath::Vector4 ClearCoatGloss;
};


class DIRECT3D11
{
private:

	//�C���X�^���X
	static DIRECT3D11* Instance;

	D3D_FEATURE_LEVEL			FeatureLevel = D3D_FEATURE_LEVEL_11_0;

	ID3D11Device*				Device;					//�f�o�C�X�@�|���S����摜�����
	ID3D11DeviceContext*		DeviceContext;			//�f�o�C�X�R���e�L�X�g �o�b�N�o�b�t�@�ɕ`��
	IDXGISwapChain*				SwapChain;				//�X���b�v�`�F�C���@��ʂ̐؂�ւ��̊Ǘ������Ă��� 60FPS�Ȃǂ̐���
	ID3D11RenderTargetView*		RenderTargetView;		//�����_�[�^�[�Q�b�g�@�`���
	ID3D11DepthStencilView*		DepthStencilView;		//

	ID3D11Buffer*				WorldBuffer;
	ID3D11Buffer*				ViewBuffer;
	ID3D11Buffer*				ProjectionBuffer;
	ID3D11Buffer*				MaterialBuffer;
	ID3D11Buffer*				LightBuffer;
	ID3D11Buffer*				PointLightBuffer;
	ID3D11Buffer*				EyeInfoBuffer;
	ID3D11Buffer*				EnvironmentMapInfoBuffer;
	ID3D11Buffer*				UIInfoBuffer;
	ID3D11Buffer*				SystemInfoBuffer;
	ID3D11Buffer*				Disney_MaterialBuffer;

	ID3D11DepthStencilState*	DepthStateEnable;
	ID3D11DepthStencilState*	DepthStateDisable;

	ID3D11BlendState*			BlendState;
	ID3D11BlendState*			BlendStateATC;

	Application*				App;

public:

	//=================================================
	//�yDirect3D11�V�X�e���N���X�̃Q�b�^�[�z
	//�E�C���X�^���X����������Ă��Ȃ���΍쐬
	static DIRECT3D11* Get_Instance()
	{
		//�����ς݂̃C���X�^���X���Ȃ���ΐV�K�쐬
		if (Instance == NULL)
		{
			Instance = new DIRECT3D11();
		}

		//�C���X�^���X�̃|�C���^�[��Ԃ�
		return Instance;
	}

	//=================================================
	//DIRECT3D11�̏�����
	//_APP�F�A�v���P�[�V�����|�C���^�[
	void Init(Application* _APP);

	//=================================================
	//�����_�����O�@�t���[���J�n����
	//�`�揈���̑O
	void Render_DrawBegin();


	//=================================================
	//�����_�����O�@�t���[���I������
	//�`�揈���̌�
	void Render_DrawEnd();

	//=================================================
	//
	void SetDepthEnable(bool Enable);

	//=================================================
	//
	void SetATCEnable(bool Enable);

	//=================================================
	//
	void SetWorldViewProjection2D();

	//=================================================
	//
	void SetWorldMatrix(DirectX::XMMATRIX* WorldMatrix);

	//=================================================
	//
	void SetViewMatrix(DirectX::XMMATRIX* ViewMatrix);

	//=================================================
	//
	void SetProjectionMatrix(DirectX::XMMATRIX* ProjectionMatrix);

	//=================================================
	//
	void SetMaterial(MATERIAL Material);

	//=================================================
	//
	void SetLight(LIGHT Light);

	//=================================================
	//
	void SetPointLight(LIGHT_POINT Light_Point);

	//=================================================
	//
	void SetEyeInfo(EYE_INFO Eye_Info);

	//=================================================
	//
	void SetEnvironmentMapInfo(ENVIRONMENTMAP_INFO EnvironmentMap_Info);

	//=================================================
	//
	void SetUIInfoBuffer(DirectX::XMMATRIX* _UI_Info);

	//=================================================
	//
	void SetGPUSystemInfo(GPU_SYSTEM_INFO _System_Info);

	//=================================================
	//
	void SetDisneyMaterial(DISNEY_MATERIAL _Disney_Material);

	//=================================================
	//
	void CreateVertexShader(ID3D11VertexShader** VertexShader, ID3D11InputLayout** VertexLayout, const char* FileName);
	
	//=================================================
	//
	void CreatePixelShader(ID3D11PixelShader** PixelShader, const char* FileName);

	//DIRECT3D11�̉������
	void Release();


	//=================================================
	//�y�Q�b�^�[�z

	Application* Get_ApplicationHandle()
	{
		return App;
	}

	D3D_FEATURE_LEVEL Get_D3D_FEATURE_LEVEL()
	{
		return FeatureLevel;
	}

	ID3D11Device* Get_ID3D11Device()
	{
		return D3D->Device;
	}

	ID3D11DeviceContext* Get_ID3D11DeviceContext()
	{
		return D3D->DeviceContext;
	}

	IDXGISwapChain* Get_IDXGISwapChain()
	{
		return D3D->SwapChain;
	}

	ID3D11RenderTargetView* Get_RenderTargetView()
	{
		return D3D->RenderTargetView;
	}

	ID3D11DepthStencilView* Get_ID3D11DepthStencilView()
	{
		return D3D->DepthStencilView;
	}

	ID3D11Buffer* Get_WorldBuffer()
	{
		return D3D->WorldBuffer;
	}

	ID3D11Buffer* Get_ViewBuffer()
	{
		return D3D->ViewBuffer;
	}

	ID3D11Buffer* Get_ProjectionBuffer()
	{
		return D3D->ProjectionBuffer;
	}

	ID3D11Buffer* Get_MaterialBuffer()
	{
		return D3D->MaterialBuffer;
	}

	ID3D11Buffer* Get_LightBuffer()
	{
		return D3D->LightBuffer;
	}

	ID3D11DepthStencilState* Get_DepthStateEnable()
	{
		return D3D->DepthStateEnable;
	}

	ID3D11DepthStencilState* Get_DepthStateDisable()
	{
		return D3D->DepthStateDisable;
	}

	ID3D11BlendState* Get_BlendState()
	{
		return D3D->BlendState;
	}

	ID3D11BlendState* Get_BlendStateATC()
	{
		return D3D->BlendStateATC;
	}
};