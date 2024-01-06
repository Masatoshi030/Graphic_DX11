#include "DITEngine3D.h"

#include <DirectXMath.h>

using namespace DirectX;

void Transform::Init()
{
	// 座標・角度・スケール　初期化
	position = Vector3(0.0f, 0.0f, 0.0f);
	rotation = Vector3(0.0f, 0.0f, 0.0f);
	scale = Vector3(1.0f, 1.0f, 1.0f);
}

void Transform::Translate(Vector3 value)
{
	Translate(value.x, value.y, value.z);
}

void Transform::Update() 
{
	// ワールド変換行列の計算

	XMMATRIX scal, rot, trans;

	// スケール
	scal = XMMatrixScaling(gameObject->transform->scale.x, gameObject->transform->scale.y, gameObject->transform->scale.z);

	// 回転
	rot = XMMatrixRotationRollPitchYaw(gameObject->transform->rotation.x, gameObject->transform->rotation.y, gameObject->transform->rotation.z);

	// 位置
	trans = XMMatrixTranslation(gameObject->transform->position.x, gameObject->transform->position.y, gameObject->transform->position.z);

	// 合成
	worldMatrix = scal * rot * trans;

	//もし親がいたら
	if (gameObject->parent != nullptr)
	{
		//親の座標系に直す
		worldMatrix = worldMatrix * gameObject->parent->transform->worldMatrix;
	}
}

void Transform::Translate(float _x, float _y, float _z)
{
	// 右向きベクトルを計算
	Vector3 rightVector;
	rightVector = QuaternionRotation_Vector3(Vector3::Right());

	//上向きベクトルを計算
	Vector3 upVector;
	upVector = QuaternionRotation_Vector3(Vector3::Up());

	// 前向きベクトルを計算する
	Vector3 forwardVector;
	forwardVector = QuaternionRotation_Vector3(Vector3::Forward());


	// 移動処理

	// X軸
	position.x += rightVector.x * _x;
	position.y += rightVector.y * _x;
	position.z += rightVector.z * _x;

	//Y軸
	position.x += upVector.x * _y;
	position.y += upVector.y * _y;
	position.z += upVector.z * _y;

	// Z軸
	position.x += forwardVector.x * _z;
	position.y += forwardVector.y * _z;
	position.z += forwardVector.z * _z;
}

void Transform::Rotate(Vector3 value)
{
	rotation += value;
}

void Transform::Rotate(float _x, float _y, float _z)
{
	rotation.x += _x;
	rotation.y += _y;
	rotation.z += _z;
}

Vector4 Transform::GetRotation_Quaternion()
{
	XMVECTOR xmVec;

	xmVec = XMQuaternionRotationRollPitchYaw(rotation.x, rotation.y, rotation.z);

	return Vector4(xmVec.m128_f32[0], xmVec.m128_f32[1], xmVec.m128_f32[2], xmVec.m128_f32[3]);
}

Vector3 Transform::QuaternionRotation_Vector3(Vector3 _Value)
{
	//回転量をXMVECTORに変換
	XMFLOAT3 _Value_f3 = _Value.xmfloat3;
	XMVECTOR _Value_xmvec = XMLoadFloat3(&_Value_f3);

	//rotationを四元数化
	XMFLOAT4 rotation_f4 = GetRotation_Quaternion().xmfloat4;
	XMVECTOR rotation_xmvec = XMLoadFloat4(&rotation_f4);

	//XMVECTORに直したVEC3で四元数に変換したrotationを回転
	XMVECTOR vec = XMVector3Rotate(_Value_xmvec, rotation_xmvec);

	return Vector3(vec.m128_f32[0], vec.m128_f32[1], vec.m128_f32[2]);
}