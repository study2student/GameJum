#pragma once

#include "Common/Vector2.h"
#include "Common/Vector2F.h"

class Player;
class GameScene;

class Enemy
{
public:
	// 画像サイズ
	static constexpr int SIZE_X = 24;
	static constexpr int SIZE_Y = 24;

	// 当たり判定用サイズ
	static constexpr int HITBOX_X = 24;
	static constexpr int HITBOX_Y = 24;	
	
	// 弾発射用の当たり判定サイズ
	static constexpr int BULETTBOX_X = 34;
	static constexpr int BULETTBOX_Y = SIZE_Y + 275;

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

	// 衝突座標（左右）
	enum class COL_LR
	{
		C, // 中央
		L, // 左
		R  // 右
	};

	// 衝突座標（上下）
	enum class COL_TD
	{
		C, // 中央
		T, // 上
		D  // 下
	};

	Enemy(void);

	~Enemy(void);

	void Init(GameScene* scene_);		// 初期化処理

	void Update(void);		// 更新処理

	void Draw(void);		// 描画処理
		
	void Release(void);		// 解放処理

	void EnemyDraw(void);	// 敵の描画
	void BulletDraw(void);	// 弾の描画

	// 移動処理
	void Move(void);
	void Walk(void);		// 移動処理（歩く）
	void Run(void);			// 移動処理（走る）

	
	// 発射処理
	void ShotActive(void);
	void Shot(void);
	void ClearBullet(void);

	// 敵のPos
	Vector2F GetEnemyPos(void);
	void SetEnemyPos(Vector2F value);	
	
	// 弾のPow
	Vector2 GetBulletPow(void);
	
	// 弾のPos
	Vector2 GetBulletPos(void);
	void SetBulletPos(Vector2F value);

	// デバッグ用
	void Debug(void);		// キーを押下すると状態切り替え
	void DrawDebug(void);	// DrawStringまとめ

private:
	GameScene* gameScene_;
	Player* player1_;
	Player* player2_;

	// キャラ用-------------------------------------------------------------------
	
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

	// 弾--------------------------------------------------------------

	// 弾の画像
	int imgBullet_;

	// 弾のスピード
	float speed;

	// 弾の半径
	float bulletRadius;

	// 弾の移動量
	Vector2 bulletPow_;

	// 弾の座標
	Vector2 bulletPos_;

	// 弾が生存中かどうか
	bool isBullet_;

	// -------------------------------------------------------------------

	// 当たり判定用-------------------------------------------------------
	
	// 衝突判定用：中心座標（pos_からの相対座標）
	Vector2 hitPos_;

	// 衝突判定用：範囲
	Vector2 hitBox_;

	// 衝突座標を取得する
	Vector2 GetColPos(COL_LR lr, COL_TD td);

	// ランダムに状態が切り替わる
	void RandState(void);

	// 経過時間を返す
	int GetTime(void);

	// ランダム用変数
	int blink_;
	int rand_;

	bool stateRand_;

	// 経過時間取得用変数
	int startTime;
	int elapsedTime;
};

