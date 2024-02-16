#pragma once
#include "Component.h"
class Spring : public Component
{
private:

	float MaxStretch = 1.0f;

	float MinStretch = 0.0f;

	float Stretch = 0.0f;

	float LastStretch = 0.0f;

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

	bool StretchVec_X = false;
	bool StretchVec_Y = true;
	bool StretchVec_Z = false;

	float StretchSpeed = 0.0005f;

	void SetStretchMaxMin(float _max, float _min);

	void SetStretch(float _stretch);
};

