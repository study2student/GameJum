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
	// 敵の初期化
	if (enemy_ == nullptr)
	{
		enemy_ = new Enemy();
	}
	enemy_->Init();

	bulletGimmick_ = new BulletGimmick();
	bulletGimmick_->Init();

	//player_ = new Player();
	//player_->Init();

	player_[0] = new Player();
	Player::KEY_CONFIG keyP1 = {
		KEY_INPUT_UP, KEY_INPUT_DOWN, KEY_INPUT_LEFT,
		KEY_INPUT_RIGHT, KEY_INPUT_N, KEY_INPUT_M
	};
	player_[0]->Init(this, Player::TYPE::PLAYER_1, keyP1);

	// プレイヤー2
	player_[1] = new Player();
	Player::KEY_CONFIG keyP2 = {
		KEY_INPUT_W, KEY_INPUT_S, KEY_INPUT_A,
		KEY_INPUT_D, KEY_INPUT_LCONTROL, KEY_INPUT_LSHIFT
	};
	player_[1]->Init(this, Player::TYPE::PLAYER_2, keyP2);
}

void GameScene::Update(void)
{

	enemy_->Update();

	bulletGimmick_->Update();

	// プレイヤー達の更新
	for (int i = 0; i < GAME_PLAYER_NUM; i++)
	{
		// プレイヤー更新
		player_[i]->Update();
	}

}

void GameScene::Draw(void)
{
	enemy_->Draw();
	DrawFormatString(100, 100, 0xff0000, "Game");
	bulletGimmick_->Draw();

	// プレイヤー達の描画
	for (int i = 0; i < GAME_PLAYER_NUM; i++)
	{
		// プレイヤー描画
		player_[i]->Draw();

	}
}

void GameScene::Release(void)
{
	// プレイヤー達の解放
	for (int i = 0; i < GAME_PLAYER_NUM; i++)
	{
		player_[i]->Release();
		delete player_[i];
	}

}
