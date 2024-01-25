#pragma once
#include "Component.h"
#include "SystemFormat.h"

// �J������\���N���X
class Camera : public Component
{

private:

	DirectX::XMMATRIX viewMatrix;

	bool lookAt = false;

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


	//lookAt
	void Set_lookAt(bool _value)
	{
		lookAt = _value;
	}

	bool Get_lookAt()
	{
		return lookAt;
	}

};