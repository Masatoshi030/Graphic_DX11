#pragma once

#include <d3d11.h>
#include <SimpleMath.h>
#include <DirectXMath.h>

//他の型に対応したVecotr4クラス
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


	//デフォルトコンストラクタ
	Vector4();

	//================================================
	//4要素格納
	//_x：X値　_y：Y値　_z：Z値
	Vector4(float _x, float _y, float _z, float _w);

	//================================================
	//全ての要素を0.0fにする
	void Zero();


	//演算子のオーバーロード

	//加算
	Vector4 operator +(Vector4 r);

	//減算
	Vector4 operator -(Vector4 r);

	//乗算
	Vector4 operator *(Vector4 r);

	//除算
	Vector4 operator /(Vector4 r);

	//加算
	Vector4 operator +=(Vector4 r);

	//減算
	Vector4 operator -=(Vector4 r);

	//乗算
	Vector4 operator *=(Vector4 r);

	//除算
	Vector4 operator /=(Vector4 r);
};



//他の型に対応したVecotr3クラス
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


	//デフォルトコンストラクタ
	Vector3();

	//================================================
	//3要素格納
	//_x：X値　_y：Y値　_z：Z値
	Vector3(float _x, float _y, float _z);

	//================================================
	//全ての要素を0.0fにする
	void Zero();

	//================================================
	//上向きベクトル (0, 1, 0)
	static Vector3 Up();

	//================================================
	//前向きベクトル (0, 0, 1)
	static Vector3 Forward();
	
	//================================================
	//右向きベクトル (1, 0, 0)
	static Vector3 Right();


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
		DirectX::XMFLOAT2 xmfloat2;
		struct { float x, y; };
	};



	//デフォルトコンストラクタ
	Vector2();

	//================================================
	//3要素格納
	//_x：X値　_y：Y値
	Vector2(float _x, float _y);

	//================================================
	//XMVECTOR型で取得
	DirectX::XMVECTOR GetXMVECTOR();

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