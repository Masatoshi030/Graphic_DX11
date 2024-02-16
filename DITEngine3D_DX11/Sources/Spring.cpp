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
	//最小伸びまで縮み続ける
	if (Stretch > MinStretch)
	{
		Stretch -= StretchSpeed * Time::GetDeltaTime();
	}

	//最大伸びを超えると最大に修正
	if (Stretch > MaxStretch)
	{
		Stretch = MaxStretch;
	}

	//最小伸びを超えると最小に修正
	if (Stretch < MinStretch)
	{
		Stretch = MinStretch;
	}

	//ポジションに反映
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