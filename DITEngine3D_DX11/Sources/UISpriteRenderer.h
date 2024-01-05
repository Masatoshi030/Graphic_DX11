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

	//����������
	void Init();

	//�������
	void Release();

	//�����t���[������
	void Start();

	//�X�V����
	void Update();

	//�`�揈��
	void Draw();

	//==============================================
	//�e�N�X�`����ݒ肷��֐�
	void SetTexture(ID3D11ShaderResourceView* _Texture);

	//==============================================
	//���_�V�F�[�_�[�ƒ��_���C�A�E�g��ݒ肷��֐�
	void SetVertexShader(ID3D11VertexShader* _VertexShader, ID3D11InputLayout* _InputLayout);

	//==============================================
	//�s�N�Z���V�F�[�_�[��ݒ肷��֐�
	void SetPixelShader(ID3D11PixelShader* _PixelShader);
};