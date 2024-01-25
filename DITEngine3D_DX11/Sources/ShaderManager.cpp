#include "ShaderManager.h"
#include "DITEngine3D.h"


namespace Shader
{

	//���_�V�F�[�_�[�V�F�[�_�[���X�g
	std::unordered_map<std::string, ID3D11VertexShader*> VertexShaderList;

	//���̓��C�A�E�g���X�g
	std::unordered_map<std::string, ID3D11InputLayout*> InputLayoutList;

	//�s�N�Z���V�F�[�_�[���X�g
	std::unordered_map<std::string, ID3D11PixelShader*> PixelShaderList;

	void AddVertexShader(const char* _filePath, const char* _ElementName)
	{
		ID3D11VertexShader* vertexShader_buf;
		ID3D11InputLayout* inputLayout_buf;

		D3D->CreateVertexShader(&vertexShader_buf, &inputLayout_buf, _filePath);

		//��ԍŏ��ɓǂݍ��܂ꂽ�V�F�[�_�[�̓x�[�X�̃V�F�[�_�[�Ƃ���
		//���������Ɏ����Őݒ肳���V�F�[�_�[
		if(VertexShaderList.size() == 0)
		{
			VertexShaderList["Base"] = vertexShader_buf;
			InputLayoutList["Base"] = inputLayout_buf;
		}

		VertexShaderList[_ElementName] = vertexShader_buf;
		InputLayoutList[_ElementName] = inputLayout_buf;
	}

	void AddPixelShader(const char* _filePath, const char* _ElementName)
	{
		ID3D11PixelShader* pixelShader_buf;

		D3D->CreatePixelShader(&pixelShader_buf, _filePath);


		//��ԍŏ��ɓǂݍ��܂ꂽ�V�F�[�_�[�̓x�[�X�̃V�F�[�_�[�Ƃ���
		//���������Ɏ����Őݒ肳���V�F�[�_�[
		if (PixelShaderList.size() == 0)
		{
			PixelShaderList["Base"] = pixelShader_buf;
		}

		PixelShaderList[_ElementName] = pixelShader_buf;
	}

	ID3D11VertexShader* GetVertexShader(const char* _ElementName)
	{
		return VertexShaderList[_ElementName];
	}

	ID3D11PixelShader* GetPixelShader(const char* _ElementName)
	{
		return PixelShaderList[_ElementName];
	}

	ID3D11InputLayout* GetInputLayout(const char* _ElementName)
	{
		return InputLayoutList[_ElementName];
	}
}