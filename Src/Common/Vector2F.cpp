#include <Dxlib.h>
#include <cmath>
#include "Vector2.h"
#include "Vector2F.h"


//ベクトルの大きさを返す
float Vector2F::Magnitude() const
{
	return hypot(x,y);
}

//ベクトルの正規化
void Vector2F::Normalize()
{
	float mag = Magnitude();
	x /= mag;
	y /= mag;
}

//正規化ベクトルを返す
Vector2F Vector2F::Normalized()
{
	float mag = Magnitude();

	return Vector2F(x /= mag, y /= mag);
}

Vector2 Vector2F::ToVector2()
{
	return { static_cast<int>(x),static_cast<int>(y) };
}

void Vector2F::operator+=(const Vector2F& v)
{
	x += v.x;
	y += v.y;
}

void Vector2F::operator-=(const Vector2F& v)
{
	x -= v.x;
	y -= v.y;
}

void Vector2F::operator*=(const float scl)
{
	x *= scl;
	y *= scl;
}

Vector2F Vector2F::operator*(const float scl)
{
	return Vector2F(x * scl, y * scl);
}

Vector2F operator-(const Vector2F& va, const Vector2F vb)
{
	return Vector2F(va.x - vb.x, va.y - vb.y);
}

Vector2F operator+(const Vector2F& va, const Vector2F vb)
{
	return Vector2F(va.x + vb.x, va.y + vb.y);
}

//内積
float Dot(const Vector2F& va, const Vector2F& vb)
{
	return va.x * vb.x + va.y * vb.y;
}

//外積
float Cross(const Vector2F& va, const Vector2F& vb)
{
	return va.x * vb.y - va.y * vb.x;
}
