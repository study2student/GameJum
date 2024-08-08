#include <DxLib.h>
#include "Application.h"
#include "BulletGimmick.h"

BulletGimmick::BulletGimmick(void)
{
}

BulletGimmick::~BulletGimmick(void)
{
}

void BulletGimmick::Init(void)
{

	// íeÇÃì«Ç›çûÇ›
	LoadDivGraph("Data/Image/Gimmick/Bullet/Bullet.png",
		IMAGE_NUM,
		IMAGE_X_NUM, IMAGE_Y_NUM,
		IMAGE_X_SIZE, IMAGE_Y_SIZE,
		&image_[0][0]);

	animCnt_ = 0;

	pos_ = { 0.0f,(float)Application::SCREEN_SIZE_Y / 2 };

}

void BulletGimmick::Update(void)
{

	pos_.x -= 1.0f;

	if (pos_.x <= 0.0f)
	{
		pos_.x = Application::SCREEN_SIZE_X;
	}

}

void BulletGimmick::Draw(void)
{

	animCnt_++;

	DrawGraph(pos_.x, pos_.y, image_[(animCnt_ / 10) % IMAGE_NUM - 1][1], true);

}

void BulletGimmick::Release(void)
{
}
