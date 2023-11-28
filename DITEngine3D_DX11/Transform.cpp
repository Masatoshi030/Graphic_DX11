#include "DITEngine3D.h"

void Transform::Init()
{
	//座標・角度・スケール　初期化
	position = Vector3(0.0f, 0.0f, 0.0f);
	rotation = Vector3(0.0f, 0.0f, 0.0f);
	scale = Vector3(1.0f, 1.0f, 1.0f);
}

void Transform::Translate(Vector3 value)
{
	position += value;
}

void Transform::Translate(float _x, float _y, float _z)
{
	position.x += _x;
	position.y += _y;
	position.z += _z;
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