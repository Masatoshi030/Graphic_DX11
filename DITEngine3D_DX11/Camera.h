#pragma once
#include "Component.h"
#include "SystemFormat.h"

// �J������\���N���X
class Camera : public Component
{

private:

	Vector3 target;
	DirectX::SimpleMath::Matrix viewMatrix;

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

};