#pragma once
#include "SceneBase.h"

class Enemy;


class Player;
class BulletGimmick;

class GameScene : public SceneBase
{
public:
	// コンストラクタ
	GameScene(void);

	// デストラクタ
	~GameScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;

private:

	std::shared_ptr<Player> player_;

	// 弾のギミック
	BulletGimmick* bulletGimmick_;

	// Enemy用ポインタ
	Enemy* enemy_;

	// 衝突判定
	void GimmickCollision(void);

	// 衝突判定
	bool IsCollisionRect(Vector2 stPos1, Vector2 edPos1, Vector2 stPos2, Vector2 edPos2);

	// 衝突判定
	bool IsCollisionRectCenter(Vector2 centerPos1, Vector2 size1, Vector2 centerPos2, Vector2 size2);

};

