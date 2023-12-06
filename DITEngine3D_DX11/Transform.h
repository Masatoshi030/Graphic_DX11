#pragma once
#include "Component.h"
#include "SystemFormat.h"


class Transform : public Component
{
public:
	//�R�������W
	Vector3 position;
	
	//�R�����p�x
	Vector3 rotation;

	//�R�����X�P�[��
	Vector3 scale;

	//���[���h�ϊ��s��
	DirectX::XMMATRIX worldMatrix;

	void Init();

	void Update();

	void Translate(Vector3 value);
	void Translate(float _x, float _y, float _z);

	void Rotate(Vector3 value);
	void Rotate(float _x, float _y, float _z);
};