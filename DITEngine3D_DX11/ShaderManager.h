#pragma once
#include "SystemFormat.h"
#include "utftosjisconv.h"
#include <string>
#include <unordered_map>

namespace Shader
{

	//�V�F�[�_�[�Ǘ��p�\����
	struct SHADER_ELEMENT
	{
		ID3D11VertexShader* VertexShader{};
		ID3D11PixelShader* PixelShader{};
		ID3D11InputLayout* VertexLayout{};
	};

	//==================================================
	//�V�F�[�_�[���쐬���ă��[�h
	void AddShader(const char* _VertexShader_FileName, const char* _PixelShader_FileName, const char* _ElementName);

	//==================================================
	//�V�F�[�_�[���܂Ƃ߂Ď擾
	SHADER_ELEMENT* GetShader(const char* _ElementName);

	//==================================================
	//���_�V�F�[�_�[���擾
	ID3D11VertexShader* GetVertexShader(const char* _ElementName);

	//==================================================
	//�s�N�Z���V�F�[�_�[���擾
	ID3D11PixelShader* GetPixelShader(const char* _ElementName);

	//==================================================
	//���_���C�A�E�g���擾
	ID3D11InputLayout* GetVertexLayout(const char* _ElementName);
}