#include "ShaderManager.h"
#include "DITEngine3D.h"


namespace Shader
{

	//シェーダーリスト
	std::unordered_map<std::string, SHADER_ELEMENT*> ShaderList;


	void AddShader(const char* _VertexShader_FileName, const char* _PixelShader_FileName, const char* _ElementName)
	{
		SHADER_ELEMENT* shader_buf = new SHADER_ELEMENT;

		D3D->CreateVertexShader(&shader_buf->VertexShader, &shader_buf->VertexLayout, _VertexShader_FileName);

		D3D->CreatePixelShader(&shader_buf->PixelShader, _PixelShader_FileName);

		ShaderList[_ElementName] = shader_buf;
	}

	SHADER_ELEMENT* GetShader(const char* _ElementName)
	{
		return ShaderList[_ElementName];
	}

	ID3D11VertexShader* GetVertexShader(const char* _ElementName)
	{
		return ShaderList[_ElementName]->VertexShader;
	}

	ID3D11PixelShader* GetPixelShader(const char* _ElementName)
	{
		return ShaderList[_ElementName]->PixelShader;
	}

	ID3D11InputLayout* GetVertexLayout(const char* _ElementName)
	{
		return ShaderList[_ElementName]->VertexLayout;
	}
}