#pragma once

#include <d3d11.h>
#include <SimpleMath.h>
#include <DirectXMath.h>

//���̌^�ɑΉ�����Vecotr4�N���X
class Vector4
{
public:

	union
	{
		float float4[4];
		DirectX::SimpleMath::Vector4 simpleMath_vector4;
		DirectX::XMFLOAT4 xmfloat4;
		struct { float x, y, z, w; };
	};


	//�f�t�H���g�R���X�g���N�^
	Vector4();

	//================================================
	//4�v�f�i�[
	//_x�FX�l�@_y�FY�l�@_z�FZ�l
	Vector4(float _x, float _y, float _z, float _w);

	//================================================
	//�S�Ă̗v�f��0.0f�ɂ���
	void Zero();


	//���Z�q�̃I�[�o�[���[�h

	//���Z
	Vector4 operator +(Vector4 r);

	//���Z
	Vector4 operator -(Vector4 r);

	//��Z
	Vector4 operator *(Vector4 r);

	//���Z
	Vector4 operator /(Vector4 r);

	//���Z
	Vector4 operator +=(Vector4 r);

	//���Z
	Vector4 operator -=(Vector4 r);

	//��Z
	Vector4 operator *=(Vector4 r);

	//���Z
	Vector4 operator /=(Vector4 r);
};



//���̌^�ɑΉ�����Vecotr3�N���X
class Vector3
{
public:

	union
	{
		float float3[3];
		DirectX::SimpleMath::Vector3 simpleMath_vector3;
		DirectX::XMFLOAT3 xmfloat3;
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

	//================================================
	//������x�N�g�� (0, 1, 0)
	static Vector3 Up();

	//================================================
	//�O�����x�N�g�� (0, 0, 1)
	static Vector3 Forward();
	
	//================================================
	//�E�����x�N�g�� (1, 0, 0)
	static Vector3 Right();


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
		DirectX::XMFLOAT2 xmfloat2;
		struct { float x, y; };
	};



	//�f�t�H���g�R���X�g���N�^
	Vector2();

	//================================================
	//3�v�f�i�[
	//_x�FX�l�@_y�FY�l
	Vector2(float _x, float _y);

	//================================================
	//XMVECTOR�^�Ŏ擾
	DirectX::XMVECTOR GetXMVECTOR();

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