#include <DxLib.h>
#include "Application.h"
#include "BulletGimmick.h"
#include "Bullet.h"

BulletGimmick::BulletGimmick(void)
{
}

BulletGimmick::~BulletGimmick(void)
{
}

void BulletGimmick::Init(void)
{
	for (int i = 0; i < 3; i++)
	{
		Bullet* shot = GetAvailableShot();
	}
}

void BulletGimmick::Update(void)
{
	for (auto& bullet : bullet_)
	{
		if (bullet->GetBulletData().isAlive)
		{
			bullet->Update();
		}

		if (!bullet->GetBulletData().isAlive)
		{
			Bullet* shot = GetAvailableShot();

			shot->CreateShot();
		}
	}
}

void BulletGimmick::Draw(void)
{
	for (auto& bullet : bullet_)
	{
		bullet->Draw();
	}
}

void BulletGimmick::Release(void)
{
	for (auto& bullet : bullet_)
	{
		bullet->Release();
	}
}

std::vector<Bullet*> BulletGimmick::GetBulletData(void)
{
	return bullet_;
}

Bullet* BulletGimmick::GetAvailableShot(void)
{
	// �ė��p�T��
	for (auto& bullet : bullet_)
	{
		if (!bullet->GetBulletData().isAlive)
		{
			return bullet;
		}
	}

	// �Ȃ������ꍇ�쐬
	Bullet* newBullet = new Bullet();

	// �e�̊Ǘ��z��ɒǉ�
	bullet_.push_back(newBullet);
	return newBullet;
}