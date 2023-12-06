#pragma once
#include "Component.h"
#include "SystemFormat.h"


class Transform : public Component
{
public:
	//３次元座標
	Vector3 position;
	
	//３次元角度
	Vector3 rotation;

	//３次元スケール
	Vector3 scale;

	//ワールド変換行列
	DirectX::XMMATRIX worldMatrix;

	void Init();

	void Update();

	void Translate(Vector3 value);
	void Translate(float _x, float _y, float _z);

	void Rotate(Vector3 value);
	void Rotate(float _x, float _y, float _z);
};