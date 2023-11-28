#include "DITEngine3D.h"

void Camera::Init()
{
	//カメラ生成時の初期位置
	gameObject->transform->position = Vector3(0.0f, 0.0f, -100.0f);

	//ターゲット座標を原点へ
	target = Vector3(0.0f, 0.0f, 0.0f);
}

void Camera::Release()
{

}

void Camera::Start()
{

}

void Camera::Update()
{
	//前方向に向き続ける
	target = gameObject->transform->position;

	target.z = gameObject->transform->position.z + 1.0f;

}

void Camera::Draw()
{
	//ビュー変換行列作成
	Vector3 up = Vector3(0.0f, 1.0f, 0.0f);
	viewMatrix = DirectX::XMMatrixLookAtLH
	(
		gameObject->transform->position.simpleMath_vector3, 
		target.simpleMath_vector3, 
		up.simpleMath_vector3
	);

	D3D->SetViewMatrix(&viewMatrix);

	//視野角
	constexpr float fieldOfView = DirectX::XMConvertToRadians(45.0f);

	float aspectRatio = static_cast<float>(D3D->Get_ApplicationHandle()->Get_WindowWidth()) / static_cast<float>(D3D->Get_ApplicationHandle()->Get_WindowHeight());
	float nearPlane = 0.1f;		//ニアクリップ
	float farPlane = 1000.0f;	//ファークリップ

	//プロジェクション行列の生成
	DirectX::SimpleMath::Matrix projectionMatrix;
	projectionMatrix = DirectX::XMMatrixPerspectiveFovLH(fieldOfView, aspectRatio, nearPlane, farPlane);

	D3D->SetProjectionMatrix(&projectionMatrix);
}