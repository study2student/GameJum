#include <DxLib.h>
#include "../Application.h"
#include "../Common/Vector2.h"
#include "Player.h"

Player::Player(void)
{
}

Player::~Player(void)
{
}

void Player::Init()
{
	std::string basePath = Application::PATH_IMAGE;
	
	images = LoadGraph((basePath + "Player/Idle(1).png").c_str());
}

void Player::Update(void)
{
}

void Player::Draw(void)
{
	DrawGraph(100, 100, images, true);
}

void Player::Release(void)
{
	DeleteGraph(images);
}
