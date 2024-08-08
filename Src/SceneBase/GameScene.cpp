#include <DxLib.h>
#include "../Player/Player.h"
#include "GameScene.h"

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
}

void GameScene::Update(void)
{
	player_->Update();
}

void GameScene::Draw(void)
{
	DrawFormatString(100, 100, 0xff0000, "Game");
	player_->Draw();
}
