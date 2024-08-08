
#include "Vector2.h"

// コンストラクタ
Vector2::Vector2(void)
{
	x = 0;
	y = 0;
}

// コンストラクタ
Vector2::Vector2(int vX, int vY)
{
	x = vX;
	y = vY;
}

Vector2::Vector2(float vX, float vY)
{
}

Vector2::Vector2(const Vector2F& v)
{
	x = static_cast<int>(v.x);
	y = static_cast<int>(v.y);
}

//Vector2::Vector2(const Vector2f& v)
//{
//
//}

Vector2::~Vector2(void)
{
}

