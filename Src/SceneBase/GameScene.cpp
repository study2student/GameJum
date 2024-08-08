#include <DxLib.h>
#include "../Enemy.h"
#include "GameScene.h"

GameScene::GameScene(void)
{
	enemy_ = nullptr;
}

GameScene::~GameScene(void)
{
}

void GameScene::Init(void)
{
	// “G‚Ì‰Šú‰»
	if (enemy_ == nullptr)
	{
		enemy_ = new Enemy();
	}
	enemy_->Init();
}

void GameScene::Update(void)
{
	enemy_->Update();
}

void GameScene::Draw(void)
{
	enemy_->Draw();
}
