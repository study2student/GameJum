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

	bulletGimmick_ = new BulletGimmick();
	bulletGimmick_->Init();

	//player_ = new Player();
	//player_->Init();

	// �G�̏�����
	if (enemy_ == nullptr)
	{
		enemy_ = new Enemy();
	}
	enemy_->Init(this);

	player_[0] = new Player();
	Player::KEY_CONFIG keyP1 = {
		KEY_INPUT_UP, KEY_INPUT_DOWN, KEY_INPUT_LEFT,
		KEY_INPUT_RIGHT, KEY_INPUT_N, KEY_INPUT_M
	};
	Player::PAD_CONFIG padP1 = {
	PAD_INPUT_UP, PAD_INPUT_DOWN, PAD_INPUT_LEFT,
	PAD_INPUT_RIGHT, PAD_INPUT_5, PAD_INPUT_3
	};
	player_[0]->Init(this, Player::TYPE::PLAYER_1, keyP1, padP1, InputManager::JOYPAD_NO::PAD1);

	// �v���C���[2
	player_[1] = new Player();
	Player::KEY_CONFIG keyP2 = {
		KEY_INPUT_W, KEY_INPUT_S, KEY_INPUT_A,
		KEY_INPUT_D, KEY_INPUT_LCONTROL, KEY_INPUT_LSHIFT
	};

	//�X�e�[�W�̓ǂݍ���
	stage_ = new Stage();
	stage_->Init();

	Player::PAD_CONFIG padP2 = {
	PAD_INPUT_UP, PAD_INPUT_DOWN, PAD_INPUT_6,
	PAD_INPUT_A, PAD_INPUT_5, PAD_INPUT_A
	};
	player_[1]->Init(this, Player::TYPE::PLAYER_2, keyP2, padP2, InputManager::JOYPAD_NO::PAD2);

}
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

	EnemyCollision();
	ShotCollision();

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

void GameScene::EnemyCollision(void)
{
	// �G�̈ʒu��Vector2��
	Vector2 enemyPos = enemy_->GetEnemyPos().ToVector2();
	Vector2 eHitBox = { enemy_->HITBOX_X,enemy_->HITBOX_Y };

	for (int i = 0; i < GAME_PLAYER_NUM; i++)
	{
		Vector2 playerPos = player_[i]->GetPos().ToVector2();
		Vector2 pHitBox = { player_[i]->SIZE_X,player_[i]->SIZE_Y };

		if (IsCollisionRectCenter(enemyPos, eHitBox, playerPos, pHitBox))
		{
			player_[i]->Damage(1);
		}
	}
}

void GameScene::ShotCollision(void)
{
	// �G�̈ʒu��Vector2��
	Vector2 enemyPos = enemy_->GetEnemyPos().ToVector2();
	Vector2 eHitBox = { enemy_->BULETTBOX_X,enemy_->BULETTBOX_Y };

	for (int i = 0; i < GAME_PLAYER_NUM; i++)
	{
		Vector2 playerPos = player_[i]->GetPos().ToVector2();
		Vector2 pHitBox = { player_[i]->SIZE_X,player_[i]->SIZE_Y };

		if (IsCollisionRectCenter(enemyPos, eHitBox, playerPos, pHitBox))
		{
			enemy_->ShotActive();
		}
	}
}

void GameScene::BulletCollision(void)
{
	// �G�̈ʒu��Vector2��
	Vector2 bulletPos = enemy_->GetEnemyPos().ToVector2();
	Vector2 eHitBox = { enemy_->BULETTBOX_X,enemy_->BULETTBOX_Y };

	for (int i = 0; i < GAME_PLAYER_NUM; i++)
	{
		Vector2 playerPos = player_[i]->GetPos().ToVector2();
		Vector2 pHitBox = { player_[i]->SIZE_X,player_[i]->SIZE_Y };

		if (IsCollisionRectCenter(enemyPos, eHitBox, playerPos, pHitBox))
		{
			enemy_->ShotActive();
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
