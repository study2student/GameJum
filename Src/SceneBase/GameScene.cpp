#include <DxLib.h>
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "../Application.h"
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
	// ���̓ǂݍ���
	LoadSounds();

	// bgm�����ʂōĐ�
	PlaySoundMem(bgm_, DX_PLAYTYPE_LOOP);
	ChangeVolumeSoundMem(BGM_VOLUME, bgm_);

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
	Player::PAD_CONFIG padP2 = {
	PAD_INPUT_UP, PAD_INPUT_DOWN, PAD_INPUT_6,
	PAD_INPUT_A, PAD_INPUT_5, PAD_INPUT_A
	};
	player_[1]->Init(this, Player::TYPE::PLAYER_2, keyP2, padP2, InputManager::JOYPAD_NO::PAD2);	
	

	//�X�e�[�W�̓ǂݍ���
	stage_ = new Stage();
	stage_->Init();


	// �w�i�摜
	bgImage = LoadGraph("Data/Image/UI/sky.jpg");
	bgPosX1 = 1;
	bgPosX2 = BG_SIZE;

	aliveTimeP1_ = 0.0f;
	aliveTimeP2_ = 0.0f;
}


void GameScene::Update(void)
{
	// �w�i�X�N���[��
	bgPosX1 -= 5;
	bgPosX2 -= 5;
	if (bgPosX1 < -BG_SIZE)
	{
		bgPosX1 = bgPosX2 + 1200;
	}
	if (bgPosX2 < -BG_SIZE)
	{
		bgPosX2 = bgPosX1 + 1200;
	}

	enemy_->Update();

	bulletGimmick_->Update();

	// �v���C���[�B�̍X�V
	for (int i = 0; i < GAME_PLAYER_NUM; i++)
	{
		// �v���C���[�X�V
		player_[i]->Update();
	}

	stage_->Update();

	if (player_[0]->GetHp_() > 0)
	{
		aliveTimeP1_ += SceneManager::GetInstance().GetDeltaTime();
	}

	if (player_[1]->GetHp_() > 0)
	{
		aliveTimeP2_ += SceneManager::GetInstance().GetDeltaTime();
	}

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

	// �G�ƓG�̎���̓����蔻��
	EnemyCollision();
	ShotCollision();

	// �e�Ƃ̓����蔻��
	BulletCollision();

	// �X�e�[�W�Ƃ̏Փ˔���
	StageCollision();

	InputManager& ins = InputManager::GetInstance();
	if (ins.IsTrgDown(KEY_INPUT_SPACE) || (player_[0]->GetHp_() <= 0 && player_[1]->GetHp_() <= 0))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAMEOVER);
		StopSoundMem(bgm_);
	}

	if (
		ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1,InputManager::JOYPAD_BTN::RIGHT)&&
		(player_[0]->GetHp_() > 0)
		 )
	{
		PlaySounds(playerJumpSound_, SOUNDS_VOLUME);
	}
	
	if (
		ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD2,InputManager::JOYPAD_BTN::RIGHT) &&
		(player_[1]->GetHp_() > 0)
		 )
	{
		PlaySounds(playerJumpSound_, SOUNDS_VOLUME);
	}

}

void GameScene::Draw(void)
{
	DrawRotaGraph(bgPosX1, Application::SCREEN_SIZE_Y / 2, 1.8,0.0,bgImage, true);// �w�i�̕`��
	DrawRotaGraph(bgPosX2, Application::SCREEN_SIZE_Y / 2, 1.8, 0.0, bgImage, true);// �w�i�̕`��

	stage_->Draw();
	enemy_->Draw();
	//DrawFormatString(100, 100, 0xff0000, "Game");
	bulletGimmick_->Draw();

	// �v���C���[�B�̕`��
	for (int i = 0; i < GAME_PLAYER_NUM; i++)
	{
		if (player_[i]->GetHp_() > 0)
		{
			// �v���C���[�`��
			player_[i]->Draw();
			player_[i]->DrawHP(i);
		}
	}
}

void GameScene::Release(void)
{
	DeleteGraph(bgImage);

	DeleteSoundMem(bgm_);
	DeleteSoundMem(enemyShotSound_);
	DeleteSoundMem(playerJumpSound_);
	DeleteSoundMem(playerDamageSound_);

	//�X�e�[�W�̉��
	stage_->Release();

	// �G�̉��
	enemy_->Release();	
	delete enemy_;		
	enemy_ = nullptr;	

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
			if (IsCollisionRectCenter({ (int)player_[i]->GetPos().x - 50,(int)player_[i]->GetPos().y }, { 64,64 },
				data.pos, { bullet->BULLET_IMAGE_X_SIZE,bullet->BULLET_IMAGE_Y_SIZE })
				&& bullet->GetState() == Bullet::STATE::SHOT && player_[i]->GetHp_() > 0)
			{
				player_[i]->Damage(1);
				bullet->ChangeState(Bullet::STATE::BLAST);
				PlaySounds(playerDamageSound_, SOUNDS_VOLUME);
				StartJoypadVibration((int)player_[i]->GetPadID(), 1000, 300);
			}
		}
	}

}

// �G�{�̂̓����蔻��
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
			PlaySounds(playerDamageSound_, SOUNDS_VOLUME);
		}
	}
}

// �߂Â�����e�𔭎˂���p�̓����蔻��
void GameScene::ShotCollision(void)
{
	// �G�̈ʒu��Vector2��
	Vector2 enemyPos = enemy_->GetEnemyPos().ToVector2();
	Vector2 eHitBox = { enemy_->BULETTBOX_X,enemy_->BULETTBOX_Y };

	for (int i = 0; i < GAME_PLAYER_NUM; i++)
	{
		Vector2 playerPos = player_[i]->GetPos().ToVector2();
		playerPos.x = player_[i]->GetPos().x - 50.0f;
		Vector2 pHitBox = { 64,64 };

		if (IsCollisionRectCenter(enemyPos, eHitBox, playerPos, pHitBox))
		{
			enemy_->ShotActive();
			PlaySounds(enemyShotSound_, SOUNDS_VOLUME);
		}
	}
}

// �e�̓����蔻��
void GameScene::BulletCollision(void)
{
	double angleStep = 60.0 * DX_PI_F / 180.0;
	int circle_num = 6;

	for (int i = 0; i < circle_num; i++)
	{
		double angleC = i * angleStep;

		// �e�̈ʒu��Vector2��
		Vector2 bulletPos = enemy_->GetBulletPos();
		Vector2 bulletPow = enemy_->GetBulletPow();
		// �G�̈ʒu��Vector2��
		Vector2 enemyPos = enemy_->GetEnemyPos().ToVector2();
		Vector2 bHitBox = { 10,10 };

		bulletPos.x = enemyPos.x + static_cast<int>(bulletPow.x * cos(angleC));
		bulletPos.y = enemyPos.y + static_cast<int>(bulletPow.y * sin(angleC));

		for (int i = 0; i < GAME_PLAYER_NUM; i++)
		{
			Vector2 playerPos = player_[i]->GetPos().ToVector2();
			Vector2 pHitBox = { player_[i]->SIZE_X,player_[i]->SIZE_Y };

			if (IsCollisionRectCenter(bulletPos, bHitBox, playerPos, pHitBox))
			{
				player_[i]->Damage(1);
				enemy_->ClearBullet();
				PlaySounds(playerDamageSound_, SOUNDS_VOLUME);
			}
		}
	}
}

void GameScene::StageCollision(void)
{
	for (int i = 0; i < GAME_PLAYER_NUM; i++)
	{
		for (auto& ground : stage_->GetGround())
		{
			auto data = stage_->GetGround();
			Vector2 stageCecter = { static_cast<int>(ground.pos_.x + ground.size_.x / 2),
									static_cast<int>(ground.pos_.y + ground.size_.y / 2) };

			if (IsCollisionRectCenter(player_[i]->GetPos(), { player_[i]->SIZE_X,player_[i]->SIZE_Y },
				stageCecter, ground.size_))
			{
				//�v���C���[�̍��W�����炷����
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

// �ǂݍ��񂾉����Đ�����p
void GameScene::PlaySounds(int SoundName, int Vol)
{
	// �����Đ����łȂ���΍Đ��J�n
	if (!(CheckSounds(SoundName)))
	{
		ChangeVolumeSoundMem(Vol, SoundName);
		PlaySoundMem(SoundName, DX_PLAYTYPE_BACK);
	}// �Đ����I��������m�F����
}

// �ǂݍ��ݗp
bool GameScene::LoadSounds(void)
{
	std::string basePath = Application::PATH_SOUNDS;

	bgm_ = LoadSoundMem((basePath + "bgm.mp3").c_str());
	enemyShotSound_ = LoadSoundMem((basePath + "Enemy/shot.mp3").c_str());
	playerJumpSound_ = LoadSoundMem((basePath + "Player/jump.mp3").c_str());
	playerDamageSound_ = LoadSoundMem((basePath + "Player/damage.mp3").c_str());

	return true;
}

// �����Đ������ǂ������f����p
bool GameScene::CheckSounds(int SoundName)
{
	// �Đ����I��������m�F����
	if (CheckSoundMem(SoundName) == 0)
	{
		return false; // �Đ����I�����
	}
	else
	{
		return true;
	}
}

Vector2 GameScene::World2MapPos(Vector2 worldPos)
{
	Vector2 ret;

	int mapX = worldPos.x / Stage::SIZE_X;
	int mapY = worldPos.y / Stage::SIZE_Y;

	ret.x = mapX;
	ret.y = mapY;

	return ret;
}

bool GameScene::IsCollisionStage(Vector2 worldSPos, Vector2 worldEPos)
{

	for (auto& ground : stage_->GetGround())
	{
		
		int sx = ground.pos_.x;
		int sy = ground.pos_.y;
		//int ex = ground.pos_.x + Stage::SIZE_X * 16;
		int ey = ground.pos_.y + Stage::SIZE_Y * 4;	
		int ex = ground.pos_.x + ground.size_.x;

		if (IsCollisionRect(Vector2(sx, sy), Vector2(ex, ey), worldSPos, worldEPos))
		{
			return true;

		}


	}


	return false;

	// ���[���h���W����}�b�v���W�ɕϊ�����
	//Vector2 mapPos = World2MapPos(worldPos);

	////�}�b�v����
	//mapPos.y -= 13;
	//if (mapPos.y < 0)
	//{
	//	return false;
	//}



	////for (auto& ground : stage_->GetGround())
	////{
	////	//�X�N���[������
	////	ground.pos_.x -=  SCROLL_SPEED;
	////}


	//


	//// �}�b�v�`�b�v��8�ȏ�̏ꍇ�́A�Փ˂���
	//// �}�b�v���W����}�b�v�`�b�v�ԍ����擾����
	//int chipNo = stage_->GetChipNo(mapPos);

	//if (chipNo >= 8)
	//{
	//	return true;
	//}

	//return false;
}