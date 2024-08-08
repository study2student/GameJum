#include <DxLib.h>
#include "GameScene.h"
#include "../Player/Player.h"
#include "../BulletGimmick.h"

GameScene::GameScene(void)
{
}

GameScene::~GameScene(void)
{
}

void GameScene::Init(void)
{
	player_ = std::make_shared<Player>();
	player_->Init();

	bulletGimmick_ = new BulletGimmick();
	bulletGimmick_->Init();
}

void GameScene::Update(void)
{
	player_->Update();
	bulletGimmick_->Update();
}

void GameScene::Draw(void)
{
	DrawFormatString(100, 100, 0xff0000, "Game");
	player_->Draw();
	bulletGimmick_->Draw();
}
