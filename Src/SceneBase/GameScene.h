#pragma once
#include "SceneBase.h"
class Enemy;
class Vector2;
class Player;
class BulletGimmick;

class GameScene : public SceneBase
{
public:
	static constexpr int GAME_PLAYER_NUM = 2;

	// コンストラクタ
	GameScene(void);

	// デストラクタ
	~GameScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

private:

	// 弾のギミック
	BulletGimmick* bulletGimmick_;

	// Enemy用ポインタ
	Enemy* enemy_;

	// プレイヤークラスのポインタ
	Player* player_[GAME_PLAYER_NUM];

	// 生存時間
	float aliveTimeP1_;
	float aliveTimeP2_;

	// 衝突判定
	void GimmickCollision(void);

	// 衝突判定
	bool IsCollisionRect(Vector2 stPos1, Vector2 edPos1, Vector2 stPos2, Vector2 edPos2);

	// 衝突判定
	bool IsCollisionRectCenter(Vector2 centerPos1, Vector2 size1, Vector2 centerPos2, Vector2 size2);

};

