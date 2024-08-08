#pragma once
#include "SceneBase.h"

class Enemy;


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
<<<<<<< Updated upstream

	std::shared_ptr<Player> player_;

	// 弾のギミック
	BulletGimmick* bulletGimmick_;


private:

	// Enemy用ポインタ
	Enemy* enemy_;
=======
	// プレイヤークラスのポインタ
	Player* player_[GAME_PLAYER_NUM];


>>>>>>> Stashed changes
};

