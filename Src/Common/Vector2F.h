#pragma once
class Vector2;

struct Vector2F
{
	float x,y;

	Vector2F() : x(0.0f), y(0.0f){};

	Vector2F(float vX, float vY) : x(vX), y(vY){};
	Vector2F(int vX, int vY){
		x = (float)vX;
		y = (float)vY;
	};

	//�x�N�g���̑傫����Ԃ�
	float Magnitude()const;

	//�x�N�g���̐��K��
	void Normalize();

	//���K���x�N�g����Ԃ�
	Vector2F Normalized();

	Vector2 ToVector2();

	void operator+=(const Vector2F& v);
	void operator-=(const Vector2F& v);
	void operator*=(const float scl);

	Vector2F operator* (const float scl);
	//Vector2f operator- ()
	//{
	//	return Vector2f(-x, -y);
	//};

}; 

Vector2F operator-(const Vector2F& va, const Vector2F vb);
Vector2F operator+(const Vector2F& va, const Vector2F vb);

//���ς�Ԃ�
float Dot(const Vector2F& va, const Vector2F& vb);

//�O�ς�Ԃ�
float Cross(const Vector2F& va, const Vector2F& vb);



