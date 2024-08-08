#pragma once

#include "Common/Vector2.h"
#include "Common/Vector2F.h"

class Enemy
{
public:
	// 画像サイズ
	static constexpr int SIZE_X = 24;
	static constexpr int SIZE_Y = 24;

	// アニメーション数
	// IDLE
	static constexpr int IDLE_ANIM_NUM = 4;
	// WALK
	static constexpr int WALK_ANIM_NUM = 6;
	// KICK
	static constexpr int KICK_ANIM_NUM = 4;
	// HIT
	static constexpr int HIT_ANIM_NUM = 3;
	// RUN
	static constexpr int RUN_ANIM_NUM = 7;

	// 総アニメーション数
	static constexpr int ANIM_MAX_NUM_X = 24;
	static constexpr int ANIM_MAX_NUM_Y = 5;
	
	// 状態
	enum class STATE
	{
		IDLE,
		WALK,
		KICK,
		HIT,
		RUN
	};

	Enemy(void);

	~Enemy(void);

	void Init(void);

	void Update(void);

	void Draw(void);

	void Release(void);

private:
	// 画像格納領域
	int imgsDino_[ANIM_MAX_NUM_Y][ANIM_MAX_NUM_X];

	// 状態
	STATE state_;

	// 座標
	Vector2F pos_;

	float movePow_;

	int animNum_;

	// アニメーション用のカウンター
	int cntAnim_;

	// アニメーションスピード
	float speedAnim_;
};

