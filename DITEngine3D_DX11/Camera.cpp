#include "DITEngine3D.h"

using namespace DirectX;

void Camera::Init()
{
	//�J�����������̏����ʒu
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
	//�r���[�ϊ��s��쐬
	//Vector3 up = Vector3(0.0f, 1.0f, 0.0f);
	//viewMatrix = DirectX::XMMatrixLookAtLH
	//(
	//	gameObject->transform->position.simpleMath_vector3, 
	//	target.simpleMath_vector3, 
	//	up.simpleMath_vector3
	//);

	//�ړ��s��
	XMMATRIX moveMat;
	moveMat = XMMatrixTranslation(gameObject->transform->position.x, gameObject->transform->position.y, gameObject->transform->position.z);
	
	//��]�s��
	XMMATRIX rotMat;
	rotMat = XMMatrixRotationRollPitchYaw(gameObject->transform->rotation.x, gameObject->transform->rotation.y, gameObject->transform->rotation.z);

	//����
	XMMATRIX rot_moveMat = rotMat * moveMat;

	//�t�s��
	viewMatrix = XMMatrixInverse(nullptr, rot_moveMat);

	//�r���[�s��ݒ�
	D3D->SetViewMatrix(&viewMatrix);

	//����p
	constexpr float fieldOfView = DirectX::XMConvertToRadians(60.0f);

	float aspectRatio = static_cast<float>(D3D->Get_ApplicationHandle()->Get_WindowWidth()) / static_cast<float>(D3D->Get_ApplicationHandle()->Get_WindowHeight());
	float nearPlane = 0.1f;		//�j�A�N���b�v
	float farPlane = 1000.0f;	//�t�@�[�N���b�v

	//�v���W�F�N�V�����s��̐���
	XMMATRIX projectionMatrix;
	projectionMatrix = XMMatrixPerspectiveFovLH(fieldOfView, aspectRatio, nearPlane, farPlane);

	D3D->SetProjectionMatrix(&projectionMatrix);
}