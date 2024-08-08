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
	// �G�̏�����
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

void GameScene::GimmickCollision(void)
{

	//if (IsCollisionRectCenter(player_)
	//{
	//	// �����G�t�F�N�g�𔭐�������
	//	shot->ShotBlast();
	//	shot->Blast(shotPos);
	//	enemy->SetHP(10);
	//}

}

bool GameScene::IsCollisionRect(Vector2 stPos1, Vector2 edPos1, Vector2 stPos2, Vector2 edPos2)
{

	// ��`���m�̏Փ˔���
	// ��`�P�̍������A��`�Q�̉E���傫��
	// ��`�Q�̍������A��`�P�̉E���傫��
	if (stPos1.x < edPos2.x
		&& stPos2.x < edPos1.x
		&& stPos1.y < edPos2.y
		&& stPos2.y < edPos1.y)
	{
		return true;
	}
	return false;

}

bool GameScene::IsCollisionRectCenter(Vector2 centerPos1, Vector2 size1, Vector2 centerPos2, Vector2 size2)
{

	// ��`1(������W�A�E����W)
	Vector2 stPos1 = centerPos1;
	Vector2 edPos1 = centerPos1;
	Vector2 hSize1 = { size1.x / 2, size1.y / 2 };

	stPos1.x -= hSize1.x;
	stPos1.y -= hSize1.y;
	edPos1.x += hSize1.x;
	edPos1.y += hSize1.y;

	// ��`�Q(������W�A�E����W)
	Vector2 stPos2 = centerPos2;
	Vector2 edPos2 = centerPos2;
	Vector2 hSize2 = { size2.x / 2, size2.y / 2 };

	stPos2.x -= hSize2.x;
	stPos2.y -= hSize2.y;
	edPos2.x += hSize2.x;
	edPos2.y += hSize2.y;

	// ��`���m�̏Փ˔���
	// ��`�P�̍������A��`�Q�̉E���傫��
	// ��`�Q�̍������A��`�P�̉E���傫��
	if (IsCollisionRect(stPos1, edPos1, stPos2, edPos2))
	{
		return true;
	}
	return false;

}
