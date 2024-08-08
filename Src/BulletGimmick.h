#pragma once
#include <vector>
#include "Common/Vector2F.h"

class BulletGimmick
{

public:

	struct BulletData
	{

		// 座標
		Vector2F pos;

		// 生存フラグ
		bool isAlive;

	};

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

	// 弾のデータの取得
	std::vector<BulletData> GetBulletData(void);

private:

	// 弾のデータ
	std::vector<BulletData> bulletData_;

	// アニメーションカウンタ
	int animCnt_;

	// 画像
	int image_[IMAGE_X_NUM][IMAGE_Y_NUM];

};