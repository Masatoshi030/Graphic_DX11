#pragma once
#include "Component.h"
#include "SystemFormat.h"

// ポイントライトのコンポーネント
class PointLight : public Component
{

private:

	Vector3 attenuation;

	DirectX::SimpleMath::Color lightColor;

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

	void SetAttenuation(float _constant, float _linear, float _secondary);

	Vector3 GetAttenuation()
	{
		return attenuation;
	}

	void SetLightColor(float _r, float _g, float _b, float _a);
};