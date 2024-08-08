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

	BulletData data;
	for (int i = 0; i < 3; i++)
	{
		data.pos = { 0.0f,(float)Application::SCREEN_SIZE_Y / 2 };
		bulletData_.push_back(data);
	}
}

void BulletGimmick::Update(void)
{

	for (auto& bullet : bulletData_)
	{
		if (bullet.isAlive)
		{
			bullet.pos.x -= 10.0f;
		}

		if (bullet.pos.x <= -500.0f)
		{
			bullet.pos.x = Application::SCREEN_SIZE_X;
			bullet.isAlive = false;
		}

		int rand = GetRand(100);

		if (rand == 0 && !bullet.isAlive)
		{
			bullet.pos.y = GetRand(Application::SCREEN_SIZE_Y);
			bullet.isAlive = true;
		}
	}

}

void BulletGimmick::Draw(void)
{

	animCnt_++;

	for (auto& bullet : bulletData_)
	{
		DrawRotaGraph(bullet.pos.x + IMAGE_X_SIZE * 3, bullet.pos.y, 3.0f, 0.0f, image_[(animCnt_ / 10) % IMAGE_NUM - 1][1], true);
	}

}

void BulletGimmick::Release(void)
{
	DeleteGraph(image_[IMAGE_X_NUM][IMAGE_Y_NUM]);
}

std::vector<BulletGimmick::BulletData> BulletGimmick::GetBulletData(void)
{
	return bulletData_;
}
