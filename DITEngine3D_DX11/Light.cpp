#include "DITEngine3D.h"

//初期化処理
void PointLight::Init()
{

}

//解放処理
void PointLight::Release()
{

}

//初期フレーム処理
void PointLight::Start()
{

}

void PointLight::Update()
{
	LIGHT_POINT pl;

	//光源座標を設定
	pl.Position = DirectX::SimpleMath::Vector4
	(
		gameObject->transform->position.x,
		gameObject->transform->position.y,
		gameObject->transform->position.z,
		0.0f
	);

	//減衰度合を設定
	pl.Attenuation = DirectX::SimpleMath::Vector4(attenuation.x, attenuation.y, attenuation.z, 0.0f);

	D3D->SetPointLight(pl);
}

//描画処理
void PointLight::Draw()
{

}

void PointLight::SetAttenuation(float _constant, float _linear, float _secondary)
{
	attenuation.x = _constant;
	attenuation.y = _linear;
	attenuation.z = _secondary;
}