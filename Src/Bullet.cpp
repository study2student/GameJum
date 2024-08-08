#include <DxLib.h>
#include "Application.h"
#include "Bullet.h"

Bullet::Bullet(void)
{
	// íeÇÃì«Ç›çûÇ›
	LoadDivGraph("Data/Image/Gimmick/Bullet/Bullet.png",
		BULLET_IMAGE_NUM,
		BULLET_IMAGE_X_NUM, BULLET_IMAGE_Y_NUM,
		BULLET_IMAGE_X_SIZE, BULLET_IMAGE_Y_SIZE,
		&bulletImage_[0][0]);

	animCnt_ = 0;

	state_ = STATE::SHOT;
}

Bullet::~Bullet(void)
{
}

void Bullet::Init(void)
{
}

void Bullet::Update(void)
{
	switch (state_)
	{
	case Bullet::NONE:
		NoneUpdate();
		break;
	case Bullet::SHOT:
		ShotUpdate();
		break;
	case Bullet::BLAST:
		BlastUpdate();
		break;
	case Bullet::END:
		EndUpdate();
		break;
	}
}

void Bullet::Draw(void)
{
	switch (state_)
	{
	case Bullet::NONE:
		NoneDraw();
		break;
	case Bullet::SHOT:
		ShotDraw();
		break;
	case Bullet::BLAST:
		BlastDraw();
		break;
	case Bullet::END:
		EndDraw();
		break;
	}

	animCnt_++;
}

void Bullet::Release(void)
{
	DeleteGraph(bulletImage_[BULLET_IMAGE_X_NUM][BULLET_IMAGE_Y_NUM]);
}

Bullet::BulletData Bullet::GetBulletData(void)
{
	return bulletData_;
}

void Bullet::ChangeState(STATE state)
{
	state_ = state;
}

void Bullet::NoneUpdate(void)
{
}

void Bullet::NoneDraw(void)
{
}

void Bullet::ShotUpdate(void)
{
	if (bulletData_.isAlive)
	{
		bulletData_.pos.x -= 10.0f;
	}

	if (bulletData_.pos.x <= -500.0f)
	{
		bulletData_.pos.x = Application::SCREEN_SIZE_X;
		bulletData_.isAlive = false;
		ChangeState(STATE::END);
	}
}

void Bullet::ShotDraw(void)
{
	DrawRotaGraph(bulletData_.pos.x + BULLET_IMAGE_X_SIZE * 3, bulletData_.pos.y, 3.0f, 0.0f, bulletImage_[(animCnt_ / 10) % BULLET_IMAGE_NUM - 1][1], true);
}

void Bullet::BlastUpdate(void)
{
}

void Bullet::BlastDraw(void)
{
}

void Bullet::EndUpdate(void)
{
}

void Bullet::EndDraw(void)
{
}

void Bullet::CreateShot(void)
{
	int rand = GetRand(100);

	if (rand == 0 && !bulletData_.isAlive)
	{
		bulletData_.pos.y = GetRand(Application::SCREEN_SIZE_Y);
		bulletData_.isAlive = true;
		ChangeState(STATE::SHOT);
	}
}
