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
	//ç≈è¨êLÇ—Ç‹Ç≈èkÇ›ë±ÇØÇÈ
	if (Stretch > MinStretch)
	{
		Stretch -= StretchSpeed * Time::GetDeltaTime();
	}

	//ç≈ëÂêLÇ—Çí¥Ç¶ÇÈÇ∆ç≈ëÂÇ…èCê≥
	if (Stretch > MaxStretch)
	{
		Stretch = MaxStretch;
	}

	//ç≈è¨êLÇ—Çí¥Ç¶ÇÈÇ∆ç≈è¨Ç…èCê≥
	if (Stretch < MinStretch)
	{
		Stretch = MinStretch;
	}

	//É|ÉWÉVÉáÉìÇ…îΩâf
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