#pragma once

#include <d3d11.h>
#include <SimpleMath.h>

//他の型に対応したVecotr3クラス
class Vector3
{
public:

	union
	{
		float float3[3];
		DirectX::SimpleMath::Vector3 simpleMath_vector3;
		struct { float x, y, z; };
	};


	//デフォルトコンストラクタ
	Vector3();

	//================================================
	//3要素格納
	//_x：X値　_y：Y値　_z：Z値
	Vector3(float _x, float _y, float _z);

	//================================================
	//全ての要素を0.0fにする
	void Zero();


	//演算子のオーバーロード

	//加算
	Vector3 operator +(Vector3 r);

	//減算
	Vector3 operator -(Vector3 r);

	//乗算
	Vector3 operator *(Vector3 r);

	//除算
	Vector3 operator /(Vector3 r);

	//加算
	Vector3 operator +=(Vector3 r);

	//減算
	Vector3 operator -=(Vector3 r);

	//乗算
	Vector3 operator *=(Vector3 r);

	//除算
	Vector3 operator /=(Vector3 r);
};






//他の型に対応したVecotr2クラス
class Vector2
{
public:

	union
	{
		float float2[2];
		DirectX::SimpleMath::Vector2 simpleMath_vector2;
		struct { float x, y; };
	};



	//デフォルトコンストラクタ
	Vector2();

	//================================================
	//3要素格納
	//_x：X値　_y：Y値
	Vector2(float _x, float _y);

	//================================================
	//全ての要素を0.0fにする
	void Zero();


	//演算子のオーバーロード

	//加算
	Vector2 operator +(const Vector2 r);

	//減算
	Vector2 operator -(const Vector2 r);

	//乗算
	Vector2 operator *(const Vector2 r);

	//除算
	Vector2 operator /(const Vector2 r);

	//加算
	Vector2 operator +=(const Vector2 r);

	//減算
	Vector2 operator -=(const Vector2 r);

	//乗算
	Vector2 operator *=(const Vector2 r);

	//除算
	Vector2 operator /=(const Vector2 r);
};