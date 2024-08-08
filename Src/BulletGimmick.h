#pragma once
#include "Common/Vector2F.h"

class BulletGimmick
{

public:

	static constexpr int IMAGE_NUM = 4;

	static constexpr int IMAGE_X_NUM = 4;

	static constexpr int IMAGE_Y_NUM = 1;

	static constexpr int IMAGE_X_SIZE = 48;

	static constexpr int IMAGE_Y_SIZE = 32;

	BulletGimmick(void);

	~BulletGimmick(void);

	void Init(void);

	void Update(void);
	
	void Draw(void);

	void Release(void);

private:

	// 座標
	Vector2F pos_;

	// 画像
	int image_[IMAGE_X_NUM][IMAGE_Y_NUM];

	// アニメーションカウンタ
	int animCnt_;

};