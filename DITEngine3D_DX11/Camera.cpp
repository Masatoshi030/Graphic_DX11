#include "DITEngine3D.h"

using namespace DirectX;

void Camera::Init()
{
	//カメラ生成時の初期位置
	gameObject->transform->position = Vector3(0.0f, 1.0f, -10.0f);

}

void Camera::Release()
{

}

void Camera::Start()
{

}

void Camera::Update()
{

}

void Camera::Draw()
{
	//ビュー変換行列作成
	//Vector3 up = Vector3(0.0f, 1.0f, 0.0f);
	//viewMatrix = DirectX::XMMatrixLookAtLH
	//(
	//	gameObject->transform->position.simpleMath_vector3, 
	//	target.simpleMath_vector3, 
	//	up.simpleMath_vector3
	//);

	//移動行列
	XMMATRIX moveMat;
	moveMat = XMMatrixTranslation(gameObject->transform->position.x, gameObject->transform->position.y, gameObject->transform->position.z);
	
	//回転行列
	XMMATRIX rotMat;
	rotMat = XMMatrixRotationRollPitchYaw(gameObject->transform->rotation.x, gameObject->transform->rotation.y, gameObject->transform->rotation.z);

	//合成
	XMMATRIX rot_moveMat = rotMat * moveMat;

	//逆行列化
	viewMatrix = XMMatrixInverse(nullptr, rot_moveMat);

	//ビュー行列設定
	D3D->SetViewMatrix(&viewMatrix);

	//視野角
	constexpr float fieldOfView = DirectX::XMConvertToRadians(60.0f);

	float aspectRatio = static_cast<float>(D3D->Get_ApplicationHandle()->Get_WindowWidth()) / static_cast<float>(D3D->Get_ApplicationHandle()->Get_WindowHeight());
	float nearPlane = 0.1f;		//ニアクリップ
	float farPlane = 1000.0f;	//ファークリップ

	//プロジェクション行列の生成
	XMMATRIX projectionMatrix;
	projectionMatrix = XMMatrixPerspectiveFovLH(fieldOfView, aspectRatio, nearPlane, farPlane);

	D3D->SetProjectionMatrix(&projectionMatrix);
}