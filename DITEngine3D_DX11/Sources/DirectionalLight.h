#pragma once
#include "Component.h"
#include "SystemFormat.h"
#include "Direct3D11.h"

// �|�C���g���C�g�̃R���|�[�l���g
class DirectionalLight : public Component
{

private:

	LIGHT light;

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

	void SetLightColor(Vector4 _Color);

	void SetAmbient(Vector4 _Color);

	void SetDirection(Vector3 _Dir);
};