#include "DITEngine3D.h"

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

	XMMATRIX scale, rot, trans;

	// スケール
	scale = XMMatrixScaling(gameObject->transform->scale.x, gameObject->transform->scale.y, gameObject->transform->scale.z);

	// 回転
	rot = XMMatrixRotationRollPitchYaw(gameObject->transform->rotation.x, gameObject->transform->rotation.y, gameObject->transform->rotation.z);

	// 位置
	trans = XMMatrixTranslation(gameObject->transform->position.x, gameObject->transform->position.y, gameObject->transform->position.z);

	// 合成
	worldMatrix = scale * rot * trans;

	//もし親がいたら
	if (gameObject->parent != nullptr)
	{
		//親の座標系に直す
		worldMatrix = worldMatrix * gameObject->parent->transform->worldMatrix;
	}
}

void Transform::Translate(float _x, float _y, float _z)
{
	// 前向きベクトルを計算する
	Vector3 forwardVector;
	forwardVector.x = sinf(rotation.y);
	forwardVector.z = cosf(rotation.y);

	Vector3 rightVector;
	rightVector.x = sinf(rotation.y + XMConvertToRadians(90.0f));
	rightVector.z = cosf(rotation.y + XMConvertToRadians(90.0f));

	// 移動処理
	position.x += rightVector.x * _x;
	position.z += rightVector.z * _x;

	position.x += forwardVector.x * _z;
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