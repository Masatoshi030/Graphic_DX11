#pragma once
#include "Component.h"
#include "SystemFormat.h"

// �|�C���g���C�g�̃R���|�[�l���g
class PointLight : public Component
{

private:

	Vector3 attenuation;

	DirectX::SimpleMath::Color lightColor;

public:

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

	void SetAttenuation(float _constant, float _linear, float _secondary);

	Vector3 GetAttenuation()
	{
		return attenuation;
	}

	void SetLightColor(float _r, float _g, float _b, float _a);
};