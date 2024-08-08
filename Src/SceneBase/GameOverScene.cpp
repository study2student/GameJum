#include "../Manager/InputManager.h"
#include "../Manager/SceneManager.h"
#include "GameOverScene.h"

GameOverScene::GameOverScene(void)
{
}

GameOverScene::~GameOverScene(void)
{
}

void GameOverScene::Init(void)
{
}

void GameOverScene::Update(void)
{
	InputManager& ins = InputManager::GetInstance();
	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::TITLE);
	}
}

void GameOverScene::Draw(void)
{
	DrawFormatString(100, 100, 0xff0000, "Result");
}

void GameOverScene::Release(void)
{
}
