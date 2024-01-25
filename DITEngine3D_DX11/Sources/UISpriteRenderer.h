#pragma once
#include "Direct3D11.h"
#include "Component.h"

class UISpriteRenderer : public Component
{
private:

	ID3D11Buffer* m_VertexBuffer{};
	ID3D11ShaderResourceView* m_Texture{};

	ID3D11VertexShader* m_VertexShader{};
	ID3D11InputLayout* m_VertexLayout{};
	ID3D11PixelShader* m_PixelShader{};

public:

	UISpriteRenderer();

	//初期化処理
	void Init();

	//解放処理
	void Release();

	//初期フレーム処理
	void Start();

	//更新処理
	void Update();

	//描画処理
	void Draw();

	//==============================================
	//テクスチャを設定する関数
	void SetTexture(ID3D11ShaderResourceView* _Texture);

	//==============================================
	//頂点シェーダーと頂点レイアウトを設定する関数
	void SetVertexShader(ID3D11VertexShader* _VertexShader, ID3D11InputLayout* _InputLayout);

	//==============================================
	//ピクセルシェーダーを設定する関数
	void SetPixelShader(ID3D11PixelShader* _PixelShader);
};