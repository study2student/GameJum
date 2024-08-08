#include <DxLib.h>
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "../Player/Player.h"
#include "../Enemy.h"
#include "GameScene.h"
#include "../Player/Player.h"
#include "../BulletGimmick.h"
#include "../Stage/Stage.h"
#include "../Bullet.h"

GameScene::GameScene(void)
{
	enemy_ = nullptr;
	stage_ = nullptr;
}

GameScene::~GameScene(void)
{
}

void GameScene::Init(void)
{
	// �G�̏�����
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

	// �v���C���[2
	player_[1] = new Player();
	Player::KEY_CONFIG keyP2 = {
		KEY_INPUT_W, KEY_INPUT_S, KEY_INPUT_A,
		KEY_INPUT_D, KEY_INPUT_LCONTROL, KEY_INPUT_LSHIFT
	};
	player_[1]->Init(this, Player::TYPE::PLAYER_2, keyP2);

	//�X�e�[�W�̓ǂݍ���
	stage_ = new Stage();
	stage_->Init();
}

void GameScene::Update(void)
{

	enemy_->Update();

	bulletGimmick_->Update();

	// �v���C���[�B�̍X�V
	for (int i = 0; i < GAME_PLAYER_NUM; i++)
	{
		// �v���C���[�X�V
		player_[i]->Update();
	}

	stage_->Update();

	if (player_[0]->GetHp_() <= 0)
	{
		SceneManager::GetInstance().SetAliveTimeP1(aliveTimeP1_);
	}

	if (player_[1]->GetHp_() <= 0)
	{
		SceneManager::GetInstance().SetAliveTimeP2(aliveTimeP2_);
	}

	// ���ł���e�Ƃ̏Փ˔���
	GimmickCollision();

	InputManager& ins = InputManager::GetInstance();
	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAMEOVER);
	}

}

void GameScene::Draw(void)
{
	stage_->Draw();
	enemy_->Draw();
	DrawFormatString(100, 100, 0xff0000, "Game");
	bulletGimmick_->Draw();

	// �v���C���[�B�̕`��
	for (int i = 0; i < GAME_PLAYER_NUM; i++)
	{
		// �v���C���[�`��
		player_[i]->Draw();
		player_[i]->DrawHP(i);
	}
}

void GameScene::Release(void)
{
	//�X�e�[�W�̉��
	stage_->Release();

	// �v���C���[�B�̉��
	for (int i = 0; i < GAME_PLAYER_NUM; i++)
	{
		player_[i]->Release();
		delete player_[i];
	}

}

void GameScene::GimmickCollision(void)
{

	for (int i = 0; i < GAME_PLAYER_NUM; i++)
	{
		for (auto& bullet : bulletGimmick_->GetBulletData())
		{
			auto data = bullet->GetBulletData();
			if (IsCollisionRectCenter(player_[i]->GetPos(), { player_[i]->SIZE_X,player_[i]->SIZE_Y },
				data.pos, { bullet->BULLET_IMAGE_X_SIZE,bullet->BULLET_IMAGE_Y_SIZE }))
			{
				player_[i]->Damage(1);
			}
		}
	}

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
