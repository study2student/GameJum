#include <DxLib.h>
#include "Application.h"
#include "Enemy.h"

Enemy::Enemy(void)
{
}

Enemy::~Enemy(void)
{
}

void Enemy::Init(void)
{
	// âÊëúÇÃì«Ç›çûÇ›
	int ret;
	ret = LoadDivGraph(
		"Data/Enemy/blue.png",
		ANIM_MAX_NUM_X * ANIM_MAX_NUM_Y,
		ANIM_MAX_NUM_X,
		ANIM_MAX_NUM_Y,
		SIZE_X,
		SIZE_Y,
		&(imgsDino_[0][0])
	);

	cntAnim_ = 0;
	speedAnim_ = 0.1f;
	animNum_ = 0;
	pos_ = { Application::SCREEN_SIZE_X /2,Application::SCREEN_SIZE_Y /2};
	state_ = STATE::IDLE;
	movePow_ = 0.5f;
}

void Enemy::Update(void)
{
	cntAnim_++;

	if (CheckHitKey(KEY_INPUT_1))
	{
		state_ = STATE::IDLE;
	}	
	
	if (CheckHitKey(KEY_INPUT_2))
	{
		state_ = STATE::WALK;
	}	
	
	if (CheckHitKey(KEY_INPUT_3))
	{
		state_ = STATE::KICK;
	}	
	
	if (CheckHitKey(KEY_INPUT_4))
	{
		state_ = STATE::HIT;
	}

	if (CheckHitKey(KEY_INPUT_5))
	{
		state_ = STATE::RUN;
	}


	switch (state_)
	{
	case STATE::IDLE:
		animNum_ = static_cast<int>(
			static_cast<float>(cntAnim_) * speedAnim_)
			% IDLE_ANIM_NUM;

		break;

	case STATE::WALK:
		animNum_ = static_cast<int>(
			static_cast<float>(cntAnim_) * speedAnim_)
			% WALK_ANIM_NUM;

		pos_.x += movePow_;
		if (pos_.x > Application::SCREEN_SIZE_X / 2 + 10)
		{
			movePow_ *= -1;
		}
		if (pos_.x < Application::SCREEN_SIZE_X / 2 - 10)
		{
			movePow_ *= -1;
		}

		break;	
	
	case STATE::KICK:
		animNum_ = static_cast<int>(
			static_cast<float>(cntAnim_) * speedAnim_)
			% KICK_ANIM_NUM;
		break;

	case STATE::HIT:
		animNum_ = static_cast<int>(
			static_cast<float>(cntAnim_) * speedAnim_)
			% HIT_ANIM_NUM;
		break;

	case STATE::RUN:
		animNum_ = static_cast<int>(
			static_cast<float>(cntAnim_) * speedAnim_)
			% RUN_ANIM_NUM;
		break;

	default:
		break;
	}
}

void Enemy::Draw(void)
{

	// íÜêSç¿ïWÇ≈ï`âÊ
	DrawRotaGraph(
		pos_.x,
		pos_.y,
		1.0f,		// ägëÂ
		0.0f,		// âÒì]
		imgsDino_[static_cast<int>(state_)][animNum_],
		true,
		false);
}

void Enemy::Release(void)
{
	for (int y = 0; y < ANIM_MAX_NUM_Y; y++)
	{
		for (int x = 0; x < ANIM_MAX_NUM_X; x++)
		{
			DeleteGraph(imgsDino_[y][x]);
		}
	}

}
