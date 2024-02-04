#pragma once

//=============================================================//
//	Direct3D11をシングルトンで管理するクラス
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

//解放マクロ
#define SAFE_RELEASE(_a) if(_a!=NULL){_a->Release();_a=NULL;}



//3D頂点データ
struct VERTEX_3D
{
	DirectX::SimpleMath::Vector3 Position;
	DirectX::SimpleMath::Vector3 Normal;
	DirectX::SimpleMath::Color Diffuse;
	DirectX::SimpleMath::Vector2 TexCoord;
};


//マテリアル
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


//平行光源
struct LIGHT
{
	BOOL Enable;
	BOOL Dummy[3];
	DirectX::SimpleMath::Vector4 Direction;
	DirectX::SimpleMath::Color Diffuse;
	DirectX::SimpleMath::Color Ambient;
	DirectX::SimpleMath::Vector4 Intensity;
};


//点光源
struct LIGHT_POINT
{
	DirectX::SimpleMath::Vector4 Position;
	DirectX::SimpleMath::Vector4 Attenuation;
	DirectX::SimpleMath::Vector4 LightColor;
};


//視点情報
struct EYE_INFO
{
	DirectX::SimpleMath::Vector4 EyePosition;	//視点の座標
};


//環境マップ情報
struct ENVIRONMENTMAP_INFO
{
	DirectX::SimpleMath::Vector4 ImageSize;
};


//シェーダーに必要なシステム情報
struct GPU_SYSTEM_INFO
{
	DirectX::SimpleMath::Vector4 ScreenSize;	//xy
	DirectX::SimpleMath::Vector4 ScreenAspect;	//x
};

//Disney BRDF マテリアル
struct DISNEY_MATERIAL
{
	//ベースカラー
	DirectX::SimpleMath::Color BaseColor;
	//メタリック
	DirectX::SimpleMath::Vector4 Metallic;
	//スペキュラー強度
	DirectX::SimpleMath::Vector4 Specular;
	//ラフネス
	DirectX::SimpleMath::Vector4 Roughness;
	//異方性反射
	DirectX::SimpleMath::Vector4 Anisotropic;
	//クリアコート強度
	DirectX::SimpleMath::Vector4 ClearCoat;
	//クリアコート光沢強度
	DirectX::SimpleMath::Vector4 ClearCoatGloss;
};


class DIRECT3D11
{
private:

	//インスタンス
	static DIRECT3D11* Instance;

	D3D_FEATURE_LEVEL			FeatureLevel = D3D_FEATURE_LEVEL_11_0;

	ID3D11Device*				Device;					//デバイス　ポリゴンや画像を作る
	ID3D11DeviceContext*		DeviceContext;			//デバイスコンテキスト バックバッファに描く
	IDXGISwapChain*				SwapChain;				//スワップチェイン　画面の切り替えの管理をしている 60FPSなどの制御
	ID3D11RenderTargetView*		RenderTargetView;		//レンダーターゲット　描画先
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
	//【Direct3D11システムクラスのゲッター】
	//・インスタンスが生成されていなければ作成
	static DIRECT3D11* Get_Instance()
	{
		//生成済みのインスタンスがなければ新規作成
		if (Instance == NULL)
		{
			Instance = new DIRECT3D11();
		}

		//インスタンスのポインターを返す
		return Instance;
	}

	//=================================================
	//DIRECT3D11の初期化
	//_APP：アプリケーションポインター
	void Init(Application* _APP);

	//=================================================
	//レンダリング　フレーム開始処理
	//描画処理の前
	void Render_DrawBegin();


	//=================================================
	//レンダリング　フレーム終了処理
	//描画処理の後
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

	//DIRECT3D11の解放処理
	void Release();


	//=================================================
	//【ゲッター】

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