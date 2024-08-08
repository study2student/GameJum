#include <Dxlib.h>
#include <cmath>
#include "Vector2.h"
#include "Vector2F.h"


//�x�N�g���̑傫����Ԃ�
float Vector2F::Magnitude() const
{
	return hypot(x,y);
}

//�x�N�g���̐��K��
void Vector2F::Normalize()
{
	float mag = Magnitude();
	x /= mag;
	y /= mag;
}

//���K���x�N�g����Ԃ�
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

//����
float Dot(const Vector2F& va, const Vector2F& vb)
{
	return va.x * vb.x + va.y * vb.y;
}

//�O��
float Cross(const Vector2F& va, const Vector2F& vb)
{
	return va.x * vb.y - va.y * vb.x;
}
