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
	//初期化処理
	void Init();

	//解放処理
	void Release();

	//初期フレーム処理
	void Start();

	//更新処理
	void Update();

	//描画処理
	void Draw();

	bool StretchVec_X = false;
	bool StretchVec_Y = true;
	bool StretchVec_Z = false;

	float StretchSpeed = 0.0005f;

	void SetStretchMaxMin(float _max, float _min);

	void SetStretch(float _stretch);
};

