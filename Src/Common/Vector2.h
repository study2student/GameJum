#pragma once
#include "Vector2f.h"

class Vector2
{
public:

	int x;
	int y;

	// �R���X�g���N�^
	Vector2(void);

	// �R���X�g���N�^
	Vector2(int vX, int vY);
	Vector2(float vX, float vY);
	Vector2(const Vector2F& v);

	// �f�X�g���N�^
	~Vector2(void);

};

