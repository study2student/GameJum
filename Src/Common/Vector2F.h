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

	//ベクトルの大きさを返す
	float Magnitude()const;

	//ベクトルの正規化
	void Normalize();

	//正規化ベクトルを返す
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

//内積を返す
float Dot(const Vector2F& va, const Vector2F& vb);

//外積を返す
float Cross(const Vector2F& va, const Vector2F& vb);



