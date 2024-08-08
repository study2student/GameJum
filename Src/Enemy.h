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
	static constexpr int RUN_ANIM_NUM = 6;

	// 総アニメーション数
	static constexpr int ANIM_MAX_NUM_X = 6;
	static constexpr int ANIM_MAX_NUM_Y = 5;
	
	// アニメーションの状態
	enum class ANIM_STATE
	{
		IDLE,
		WALK,
		KICK,
		HIT,
		RUN,
		MAX
	};

	// 攻撃の状態
	enum class ATK_STATE
	{
		NONE,
		SHOT,
		MAX
	};

	// 向き
	enum class DIR
	{
		RIGHT,
		LEFT
	};

	struct Bullet {
		Vector2 pos;		// 座標
		float angle;
		Vector2 vel;		// 速度
		Vector2 accel;		// 速度
		bool isbullet;		// 存在しているか
	};

	Enemy(void);

	~Enemy(void);

	void Init(void);		// 初期化処理

	void Update(void);		// 更新処理

	void Draw(void);		// 描画処理
		
	void Release(void);		// 解放処理

	void EnemyDraw(void);
	void BulletDraw(void);

	// 移動処理
	void Walk(void);		// 移動処理（歩く）
	void Run(void);			// 移動処理（走る）

	// 発射処理
	void Shot(void);

	void Debug(void);

private:
	// 画像格納領域
	int imgsDino_[ANIM_MAX_NUM_Y][ANIM_MAX_NUM_X];

	// アニメーションの状態
	ANIM_STATE state_;

	// 攻撃の状態
	ATK_STATE atkState_;

	// 向き
	DIR dir_;

	// 座標
	Vector2F pos_;

	// 横移動する際の移動量
	float movePow_;

	// アニメーション用
	int animNum_;

	// アニメーション用のカウンター
	int cntAnim_;

	// アニメーションスピード
	float speedAnim_;

	// 
	Bullet bullets[256];

	// 弾の画像
	int imgBullet_;

	// 弾のスピード
	float speed;

	// 弾の半径
	float bulletRadius;

	Vector2 bulletPos_;

};

