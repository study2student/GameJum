#pragma once
#include "SceneBase.h"

class Enemy;


class Player;

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

private:

	// Enemy用ポインタ
	Enemy* enemy_;
};

