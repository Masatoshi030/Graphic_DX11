#include "SystemFormat.h"

//=====�@Vector3�@=====//

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

	//���ꂼ��̗v�f���m�ŉ��Z
	buf.x = this->x + r.x;
	buf.y = this->y + r.y;
	buf.z = this->z + r.z;

	return buf;
}

Vector3 Vector3::operator -(const Vector3 r)
{
	Vector3 buf;

	//���ꂼ��̗v�f���m�Ō��Z
	buf.x = this->x - r.x;
	buf.y = this->y - r.y;
	buf.z = this->z - r.z;

	return buf;
}

Vector3 Vector3::operator *(const Vector3 r)
{
	Vector3 buf;

	//���ꂼ��̗v�f���m�ŏ�Z
	buf.x = this->x * r.x;
	buf.y = this->y * r.y;
	buf.z = this->z * r.z;

	return buf;
}

Vector3 Vector3::operator /(const Vector3 r)
{
	Vector3 buf;

	//���ꂼ��̗v�f���m�ŏ��Z
	buf.x = this->x / r.x;
	buf.y = this->y / r.y;
	buf.z = this->z / r.z;

	return buf;
}

Vector3 Vector3::operator +=(const Vector3 r)
{
	//���ꂼ��̗v�f���m�ŉ��Z
	x += r.x;
	y += r.y;
	z += r.z;

	return *this;
}

Vector3 Vector3::operator -=(const Vector3 r)
{
	//���ꂼ��̗v�f���m�Ō��Z
	x -= r.x;
	y -= r.y;
	z -= r.z;

	return *this;
}

Vector3 Vector3::operator *=(const Vector3 r)
{
	//���ꂼ��̗v�f���m�ŏ�Z
	x *= r.x;
	y *= r.y;
	z *= r.z;

	return *this;
}

Vector3 Vector3::operator /=(const Vector3 r)
{
	//���ꂼ��̗v�f���m�ŏ��Z
	x /= r.x;
	y /= r.y;
	z /= r.z;

	return *this;
}







//=====�@Vector2�@=====//


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

	//���ꂼ��̗v�f���m�ŉ��Z
	buf.x = this->x + r.x;
	buf.y = this->y + r.y;

	return buf;
}

Vector2 Vector2::operator -(const Vector2 r)
{
	Vector2 buf;

	//���ꂼ��̗v�f���m�Ō��Z
	buf.x = this->x - r.x;
	buf.y = this->y - r.y;

	return buf;
}

Vector2 Vector2::operator *(const Vector2 r)
{
	Vector2 buf;

	//���ꂼ��̗v�f���m�ŏ�Z
	buf.x = this->x * r.x;
	buf.y = this->y * r.y;

	return buf;
}

Vector2 Vector2::operator /(const Vector2 r)
{
	Vector2 buf;

	//���ꂼ��̗v�f���m�ŏ��Z
	buf.x = this->x / r.x;
	buf.y = this->y / r.y;

	return buf;
}

Vector2 Vector2::operator +=(const Vector2 r)
{
	//���ꂼ��̗v�f���m�ŉ��Z
	x += r.x;
	y += r.y;

	return *this;
}

Vector2 Vector2::operator -=(const Vector2 r)
{
	//���ꂼ��̗v�f���m�Ō��Z
	x -= r.x;
	y -= r.y;

	return *this;
}

Vector2 Vector2::operator *=(const Vector2 r)
{
	//���ꂼ��̗v�f���m�ŏ�Z
	x *= r.x;
	y *= r.y;

	return *this;
}

Vector2 Vector2::operator /=(const Vector2 r)
{
	//���ꂼ��̗v�f���m�ŏ��Z
	x /= r.x;
	y /= r.y;

	return *this;
}

