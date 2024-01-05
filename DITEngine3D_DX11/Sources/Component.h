#pragma once

class Component
{
public:

	//Component�݂̂ł�new��h��
	Component() {}

	//�R���|�[�l���g�̗L������
	bool Enable = true;

	class GameObject* gameObject = nullptr;

	//�f�X�g���N�^
	~Component() {};

	//����������
	virtual void Init() {};

	//�������
	virtual void Release() {};

	//�����t���[������
	virtual void Start() {};

	//�X�V����
	virtual void Update() {};

	//�`�揈��
	virtual void Draw() {};
};