#include "DITEngine3D.h"

void Camera::Init()
{
	//�J�����������̏����ʒu
	gameObject->transform->position = Vector3(0.0f, 0.0f, -100.0f);

	//�^�[�Q�b�g���W�����_��
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
	//�O�����Ɍ���������
	target = gameObject->transform->position;

	target.z = gameObject->transform->position.z + 1.0f;

}

void Camera::Draw()
{
	//�r���[�ϊ��s��쐬
	Vector3 up = Vector3(0.0f, 1.0f, 0.0f);
	viewMatrix = DirectX::XMMatrixLookAtLH
	(
		gameObject->transform->position.simpleMath_vector3, 
		target.simpleMath_vector3, 
		up.simpleMath_vector3
	);

	D3D->SetViewMatrix(&viewMatrix);

	//����p
	constexpr float fieldOfView = DirectX::XMConvertToRadians(45.0f);

	float aspectRatio = static_cast<float>(D3D->Get_ApplicationHandle()->Get_WindowWidth()) / static_cast<float>(D3D->Get_ApplicationHandle()->Get_WindowHeight());
	float nearPlane = 0.1f;		//�j�A�N���b�v
	float farPlane = 1000.0f;	//�t�@�[�N���b�v

	//�v���W�F�N�V�����s��̐���
	DirectX::SimpleMath::Matrix projectionMatrix;
	projectionMatrix = DirectX::XMMatrixPerspectiveFovLH(fieldOfView, aspectRatio, nearPlane, farPlane);

	D3D->SetProjectionMatrix(&projectionMatrix);
}