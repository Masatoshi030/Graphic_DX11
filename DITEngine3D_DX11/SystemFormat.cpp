#include "SystemFormat.h"

//=====　Vector3　=====//

Vector3::Vector3()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

Vector3::Vector3(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
}

void Vector3::Zero()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

Vector3 Vector3::operator +(const Vector3 r)
{
	Vector3 buf;

	//それぞれの要素同士で加算
	buf.x = this->x + r.x;
	buf.y = this->y + r.y;
	buf.z = this->z + r.z;

	return buf;
}

Vector3 Vector3::operator -(const Vector3 r)
{
	Vector3 buf;

	//それぞれの要素同士で減算
	buf.x = this->x - r.x;
	buf.y = this->y - r.y;
	buf.z = this->z - r.z;

	return buf;
}

Vector3 Vector3::operator *(const Vector3 r)
{
	Vector3 buf;

	//それぞれの要素同士で乗算
	buf.x = this->x * r.x;
	buf.y = this->y * r.y;
	buf.z = this->z * r.z;

	return buf;
}

Vector3 Vector3::operator /(const Vector3 r)
{
	Vector3 buf;

	//それぞれの要素同士で除算
	buf.x = this->x / r.x;
	buf.y = this->y / r.y;
	buf.z = this->z / r.z;

	return buf;
}

Vector3 Vector3::operator +=(const Vector3 r)
{
	//それぞれの要素同士で加算
	x += r.x;
	y += r.y;
	z += r.z;

	return *this;
}

Vector3 Vector3::operator -=(const Vector3 r)
{
	//それぞれの要素同士で減算
	x -= r.x;
	y -= r.y;
	z -= r.z;

	return *this;
}

Vector3 Vector3::operator *=(const Vector3 r)
{
	//それぞれの要素同士で乗算
	x *= r.x;
	y *= r.y;
	z *= r.z;

	return *this;
}

Vector3 Vector3::operator /=(const Vector3 r)
{
	//それぞれの要素同士で除算
	x /= r.x;
	y /= r.y;
	z /= r.z;

	return *this;
}







//=====　Vector2　=====//


Vector2::Vector2()
{
	x = 0.0f;
	y = 0.0f;
}

Vector2::Vector2(float _x, float _y)
{
	x = _x;
	y = _y;
}

void Vector2::Zero()
{
	x = 0.0f;
	y = 0.0f;
}

Vector2 Vector2::operator +(const Vector2 r)
{
	Vector2 buf;

	//それぞれの要素同士で加算
	buf.x = this->x + r.x;
	buf.y = this->y + r.y;

	return buf;
}

Vector2 Vector2::operator -(const Vector2 r)
{
	Vector2 buf;

	//それぞれの要素同士で減算
	buf.x = this->x - r.x;
	buf.y = this->y - r.y;

	return buf;
}

Vector2 Vector2::operator *(const Vector2 r)
{
	Vector2 buf;

	//それぞれの要素同士で乗算
	buf.x = this->x * r.x;
	buf.y = this->y * r.y;

	return buf;
}

Vector2 Vector2::operator /(const Vector2 r)
{
	Vector2 buf;

	//それぞれの要素同士で除算
	buf.x = this->x / r.x;
	buf.y = this->y / r.y;

	return buf;
}

Vector2 Vector2::operator +=(const Vector2 r)
{
	//それぞれの要素同士で加算
	x += r.x;
	y += r.y;

	return *this;
}

Vector2 Vector2::operator -=(const Vector2 r)
{
	//それぞれの要素同士で減算
	x -= r.x;
	y -= r.y;

	return *this;
}

Vector2 Vector2::operator *=(const Vector2 r)
{
	//それぞれの要素同士で乗算
	x *= r.x;
	y *= r.y;

	return *this;
}

Vector2 Vector2::operator /=(const Vector2 r)
{
	//それぞれの要素同士で除算
	x /= r.x;
	y /= r.y;

	return *this;
}

