#pragma once
#include "SystemFormat.h"
#include "utftosjisconv.h"
#include <string>
#include <unordered_map>

namespace Shader
{

	//==================================================
	//頂点シェーダーを作成してロード
	void AddVertexShader(const char* _filePath, const char* _ElementName);


	//==================================================
	//ピクセルシェーダーを作成してロード
	void AddPixelShader(const char* _filePath, const char* _ElementName);

	//==================================================
	//頂点シェーダーを取得
	ID3D11VertexShader* GetVertexShader(const char* _ElementName);

	//==================================================
	//ピクセルシェーダーを取得
	ID3D11PixelShader* GetPixelShader(const char* _ElementName);

	//==================================================
	//頂点レイアウトを取得
	ID3D11InputLayout* GetInputLayout(const char* _ElementName);
}