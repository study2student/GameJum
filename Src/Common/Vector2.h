#pragma once
#include "Vector2f.h"

class Vector2
{
public:

	int x;
	int y;

	// コンストラクタ
	Vector2(void);

	// コンストラクタ
	Vector2(int vX, int vY);
	Vector2(float vX, float vY);
	Vector2(const Vector2F& v);

	// デストラクタ
	~Vector2(void);

};

