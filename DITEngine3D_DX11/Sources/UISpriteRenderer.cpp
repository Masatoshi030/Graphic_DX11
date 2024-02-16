#include "UISpriteRenderer.h"
#include "DITEngine3D.h"

using namespace DirectX;

UISpriteRenderer::UISpriteRenderer()
{
	VERTEX_3D vertex[4];

	vertex[0].Position = Vector3(-50.0f, -50.0f, 0.0f).simpleMath_vector3;
	vertex[0].Normal = Vector3(0.0f, 0.0f, 0.0f).simpleMath_vector3;
	vertex[0].Diffuse = DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = Vector2(0.0f, 0.0f).simpleMath_vector2;

	vertex[1].Position = Vector3(50.0f, -50.0f, 0.0f).simpleMath_vector3;
	vertex[1].Normal = Vector3(0.0f, 0.0f, 0.0f).simpleMath_vector3;
	vertex[1].Diffuse = DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = Vector2(1.0f, 0.0f).simpleMath_vector2;

	vertex[2].Position = Vector3(-50.0f, 50.0f, 0.0f).simpleMath_vector3;
	vertex[2].Normal = Vector3(0.0f, 0.0f, 0.0f).simpleMath_vector3;
	vertex[2].Diffuse = DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = Vector2(0.0f, 1.0f).simpleMath_vector2;

	vertex[3].Position = Vector3(50.0f, 50.0f, 0.0f).simpleMath_vector3;
	vertex[3].Normal = Vector3(0.0f, 0.0f, 0.0f).simpleMath_vector3;
	vertex[3].Diffuse = DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = Vector2(1.0f, 1.0f).simpleMath_vector2;

	// 頂点バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	D3D->Get_ID3D11Device()->CreateBuffer(&bd, &sd, &m_VertexBuffer);
}

//初期化処理
void UISpriteRenderer::Init()
{

}

//解放処理
void UISpriteRenderer::Release()
{

}

//初期フレーム処理
void UISpriteRenderer::Start()
{

}

//更新処理
void UISpriteRenderer::Update()
{
	XMMATRIX affine_matrix;

	//2Dのアフィン変換行列を作成
	affine_matrix = XMMatrixAffineTransformation2D(
		Vector2(gameObject->transform->scale.x, gameObject->transform->scale.y).GetXMVECTOR(),			//スケール
		Vector2(0.0f, 0.0f).GetXMVECTOR(),																//回転の中心点
		gameObject->transform->rotation.z,																//回転量（ラジアン）
		Vector2(gameObject->transform->position.x, gameObject->transform->position.y).GetXMVECTOR()		//位置
	);

	//GPUに転送
	D3D->SetUIInfoBuffer(&affine_matrix);
}

//描画処理
void UISpriteRenderer::Draw()
{
	//入力レイアウト設定
	D3D->Get_ID3D11DeviceContext()->IASetInputLayout(m_VertexLayout);

	//シェーダー設定
	D3D->Get_ID3D11DeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	D3D->Get_ID3D11DeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//マトリックス設定　2D用のマトリックス
	D3D->SetWorldViewProjection2D();

	//頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	D3D->Get_ID3D11DeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	//テクスチャ設定
	D3D->Get_ID3D11DeviceContext()->PSSetShaderResources(1, 1, &m_Texture);

	//プリミティブトポロジー設定
	D3D->Get_ID3D11DeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//ポリゴン描画
	D3D->Get_ID3D11DeviceContext()->Draw(4, 0);
}

void UISpriteRenderer::SetTexture(ID3D11ShaderResourceView* _Texture)
{
	m_Texture = _Texture;
}

//==============================================
//頂点シェーダーと頂点レイアウトを設定する関数
void UISpriteRenderer::SetVertexShader(ID3D11VertexShader* _VertexShader, ID3D11InputLayout* _InputLayout)
{
	m_VertexShader = _VertexShader;
	m_VertexLayout = _InputLayout;
}

//==============================================
//ピクセルシェーダーを設定する関数
void UISpriteRenderer::SetPixelShader(ID3D11PixelShader* _PixelShader)
{
	m_PixelShader = _PixelShader;
}