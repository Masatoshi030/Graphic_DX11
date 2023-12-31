#include "SystemFormat.h"

//=====　Vector4　=====//

Vector4::Vector4()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	w = 0.0f;
}

Vector4::Vector4(float _x, float _y, float _z, float _w)
{
	x = _x;
	y = _y;
	z = _z;
	w = _w;
}

void Vector4::Zero()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	w = 0.0f;
}

Vector4 Vector4::operator +(const Vector4 r)
{
	Vector4 buf;

	//それぞれの要素同士で加算
	buf.x = this->x + r.x;
	buf.y = this->y + r.y;
	buf.z = this->z + r.z;
	buf.w = this->w + r.w;

	return buf;
}

Vector4 Vector4::operator -(const Vector4 r)
{
	Vector4 buf;

	//それぞれの要素同士で減算
	buf.x = this->x - r.x;
	buf.y = this->y - r.y;
	buf.z = this->z - r.z;
	buf.w = this->w - r.w;

	return buf;
}

Vector4 Vector4::operator *(const Vector4 r)
{
	Vector4 buf;

	//それぞれの要素同士で乗算
	buf.x = this->x * r.x;
	buf.y = this->y * r.y;
	buf.z = this->z * r.z;
	buf.w = this->w * r.w;

	return buf;
}

Vector4 Vector4::operator /(const Vector4 r)
{
	Vector4 buf;

	//それぞれの要素同士で除算
	buf.x = this->x / r.x;
	buf.y = this->y / r.y;
	buf.z = this->z / r.z;
	buf.w = this->w / r.w;

	return buf;
}

Vector4 Vector4::operator +=(const Vector4 r)
{
	//それぞれの要素同士で加算
	x += r.x;
	y += r.y;
	z += r.z;
	w += r.w;

	return *this;
}

Vector4 Vector4::operator -=(const Vector4 r)
{
	//それぞれの要素同士で減算
	x -= r.x;
	y -= r.y;
	z -= r.z;
	w -= r.w;

	return *this;
}

Vector4 Vector4::operator *=(const Vector4 r)
{
	//それぞれの要素同士で乗算
	x *= r.x;
	y *= r.y;
	z *= r.z;
	w *= r.w;

	return *this;
}

Vector4 Vector4::operator /=(const Vector4 r)
{
	//それぞれの要素同士で除算
	x /= r.x;
	y /= r.y;
	z /= r.z;
	w /= r.w;

	return *this;
}





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

Vector3 Vector3::Up()
{
	return Vector3(0, 1.0f, 0);
}

Vector3 Vector3::Forward()
{
	return Vector3(0, 0, 1.0f);
}

Vector3 Vector3::Right()
{
	return Vector3(1.0f, 0, 0);
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

