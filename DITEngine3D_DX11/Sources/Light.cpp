#include "DITEngine3D.h"

//����������
void PointLight::Init()
{

}

//�������
void PointLight::Release()
{

}

//�����t���[������
void PointLight::Start()
{

}

void PointLight::Update()
{
	LIGHT_POINT pl;

	//�������W��ݒ�
	pl.Position = DirectX::SimpleMath::Vector4
	(
		gameObject->transform->position.x,
		gameObject->transform->position.y,
		gameObject->transform->position.z,
		0.0f
	);

	//�����x����ݒ�
	pl.Attenuation = DirectX::SimpleMath::Vector4(attenuation.x, attenuation.y, attenuation.z, 0.0f);

	//���̐F
	pl.LightColor = lightColor;

	D3D->SetPointLight(pl);
}

//�`�揈��
void PointLight::Draw()
{

}

void PointLight::SetAttenuation(float _constant, float _linear, float _secondary)
{
	attenuation.x = _constant;
	attenuation.y = _linear;
	attenuation.z = _secondary;
}

void PointLight::SetLightColor(float _r, float _g, float _b, float _a)
{
	lightColor = DirectX::SimpleMath::Color(_r, _g, _b, _a);
}