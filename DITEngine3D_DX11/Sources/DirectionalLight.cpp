#include "DITEngine3D.h"
#include "DirectionalLight.h"

using namespace DirectX;

void DirectionalLight::Init()
{

}

void DirectionalLight::Start()
{

}

void DirectionalLight::Update()
{
	//ÉâÉCÉgèÓïÒÇì]ëó
	D3D->SetLight(light);
}

void DirectionalLight::Draw()
{

}

void DirectionalLight::Release()
{

}

void DirectionalLight::SetLightColor(Vector4 _Color)
{
	light.Diffuse = SimpleMath::Color(_Color.x, _Color.y, _Color.z, _Color.w);
}

void DirectionalLight::SetAmbient(Vector4 _Color)
{
	light.Ambient = SimpleMath::Color(_Color.x, _Color.y, _Color.z, _Color.w);
}

void DirectionalLight::SetDirection(Vector3 _Dir)
{
	//åıÇÃï˚å¸Çê≥ãKâª
	_Dir.simpleMath_vector3.Normalize();
	
	light.Direction = Vector4(_Dir.x, _Dir.y, _Dir.z, 0.0f).simpleMath_vector4;
}

void DirectionalLight::SetIntensity(float _Intensity)
{
	light.Intensity.x = _Intensity;
}