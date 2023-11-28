#pragma once

#include <d3d11.h>
#include <SimpleMath.h>

//���̌^�ɑΉ�����Vecotr3�N���X
class Vector3
{
public:

	union
	{
		float float3[3];
		DirectX::SimpleMath::Vector3 simpleMath_vector3;
		struct { float x, y, z; };
	};


	//�f�t�H���g�R���X�g���N�^
	Vector3();

	//================================================
	//3�v�f�i�[
	//_x�FX�l�@_y�FY�l�@_z�FZ�l
	Vector3(float _x, float _y, float _z);

	//================================================
	//�S�Ă̗v�f��0.0f�ɂ���
	void Zero();


	//���Z�q�̃I�[�o�[���[�h

	//���Z
	Vector3 operator +(Vector3 r);

	//���Z
	Vector3 operator -(Vector3 r);

	//��Z
	Vector3 operator *(Vector3 r);

	//���Z
	Vector3 operator /(Vector3 r);

	//���Z
	Vector3 operator +=(Vector3 r);

	//���Z
	Vector3 operator -=(Vector3 r);

	//��Z
	Vector3 operator *=(Vector3 r);

	//���Z
	Vector3 operator /=(Vector3 r);
};






//���̌^�ɑΉ�����Vecotr2�N���X
class Vector2
{
public:

	union
	{
		float float2[2];
		DirectX::SimpleMath::Vector2 simpleMath_vector2;
		struct { float x, y; };
	};



	//�f�t�H���g�R���X�g���N�^
	Vector2();

	//================================================
	//3�v�f�i�[
	//_x�FX�l�@_y�FY�l
	Vector2(float _x, float _y);

	//================================================
	//�S�Ă̗v�f��0.0f�ɂ���
	void Zero();


	//���Z�q�̃I�[�o�[���[�h

	//���Z
	Vector2 operator +(const Vector2 r);

	//���Z
	Vector2 operator -(const Vector2 r);

	//��Z
	Vector2 operator *(const Vector2 r);

	//���Z
	Vector2 operator /(const Vector2 r);

	//���Z
	Vector2 operator +=(const Vector2 r);

	//���Z
	Vector2 operator -=(const Vector2 r);

	//��Z
	Vector2 operator *=(const Vector2 r);

	//���Z
	Vector2 operator /=(const Vector2 r);
};