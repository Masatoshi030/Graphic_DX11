#pragma once
#include "Component.h"
#include "SystemFormat.h"

// �|�C���g���C�g�̃R���|�[�l���g
class PointLight : public Component
{

private:

	Vector3 attenuation;

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
};