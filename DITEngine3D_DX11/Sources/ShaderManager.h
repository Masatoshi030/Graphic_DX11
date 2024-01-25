#pragma once
#include "SystemFormat.h"
#include "utftosjisconv.h"
#include <string>
#include <unordered_map>

namespace Shader
{

	//==================================================
	//���_�V�F�[�_�[���쐬���ă��[�h
	void AddVertexShader(const char* _filePath, const char* _ElementName);


	//==================================================
	//�s�N�Z���V�F�[�_�[���쐬���ă��[�h
	void AddPixelShader(const char* _filePath, const char* _ElementName);

	//==================================================
	//���_�V�F�[�_�[���擾
	ID3D11VertexShader* GetVertexShader(const char* _ElementName);

	//==================================================
	//�s�N�Z���V�F�[�_�[���擾
	ID3D11PixelShader* GetPixelShader(const char* _ElementName);

	//==================================================
	//���_���C�A�E�g���擾
	ID3D11InputLayout* GetInputLayout(const char* _ElementName);
}