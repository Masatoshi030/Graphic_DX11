#include "Spring.h"
#include "DITEngine3D.h"

void Spring::Init()
{

}

void Spring::Release()
{

}

void Spring::Start()
{

}

void Spring::Update()
{
	//�ŏ��L�т܂ŏk�ݑ�����
	if (Stretch > MinStretch)
	{
		Stretch -= StretchSpeed * Time::GetDeltaTime();
	}

	//�ő�L�т𒴂���ƍő�ɏC��
	if (Stretch > MaxStretch)
	{
		Stretch = MaxStretch;
	}

	//�ŏ��L�т𒴂���ƍŏ��ɏC��
	if (Stretch < MinStretch)
	{
		Stretch = MinStretch;
	}

	//�|�W�V�����ɔ��f
	gameObject->transform->Translate(0.0f, Stretch - LastStretch, 0.0f);

	LastStretch = Stretch;
}

void Spring::Draw()
{

}

void Spring::SetStretchMaxMin(float _max, float _min)
{
	MaxStretch = _max;
	MinStretch = _min;
}

void Spring::SetStretch(float _stretch)
{
	Stretch = _stretch;
}