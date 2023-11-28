#pragma once
#include "SystemFormat.h"
#include "utftosjisconv.h"
#include <string>
#include <unordered_map>

namespace Shader
{

	//シェーダー管理用構造体
	struct SHADER_ELEMENT
	{
		ID3D11VertexShader* VertexShader{};
		ID3D11PixelShader* PixelShader{};
		ID3D11InputLayout* VertexLayout{};
	};

	//==================================================
	//シェーダーを作成してロード
	void AddShader(const char* _VertexShader_FileName, const char* _PixelShader_FileName, const char* _ElementName);

	//==================================================
	//シェーダーをまとめて取得
	SHADER_ELEMENT* GetShader(const char* _ElementName);

	//==================================================
	//頂点シェーダーを取得
	ID3D11VertexShader* GetVertexShader(const char* _ElementName);

	//==================================================
	//ピクセルシェーダーを取得
	ID3D11PixelShader* GetPixelShader(const char* _ElementName);

	//==================================================
	//頂点レイアウトを取得
	ID3D11InputLayout* GetVertexLayout(const char* _ElementName);
}