#include <DxLib.h>
#include "../Player/Player.h"
#include "../Enemy.h"
#include "GameScene.h"
#include "../Player/Player.h"
#include "../BulletGimmick.h"

GameScene::GameScene(void)
{
	enemy_ = nullptr;
}

GameScene::~GameScene(void)
{
}

void GameScene::Init(void)
{
	player_ = std::make_shared<Player>();
	player_->Init();
	// “G‚Ì‰Šú‰»
	if (enemy_ == nullptr)
	{
		enemy_ = new Enemy();
	}
	enemy_->Init();

	bulletGimmick_ = new BulletGimmick();
	bulletGimmick_->Init();
}

void GameScene::Update(void)
{
	enemy_->Update();
	player_->Update();
	bulletGimmick_->Update();
}

void GameScene::Draw(void)
{
	enemy_->Draw();
	DrawFormatString(100, 100, 0xff0000, "Game");
	player_->Draw();
	bulletGimmick_->Draw();
}
