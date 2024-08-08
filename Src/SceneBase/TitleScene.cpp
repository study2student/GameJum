#include <DxLib.h>
#include "../Application.h"
#include "../Manager/InputManager.h"
#include "../Manager/SceneManager.h"
#include "TitleScene.h"

TitleScene::TitleScene(void)
{
}

TitleScene::~TitleScene(void)
{
}

void TitleScene::Init(void)
{

	titleImage_ = LoadGraph("Data/Image/UI/Title.png");

	gameStartImage_ = LoadGraph("Data/Image/UI/GameStart.png");

	LoadDivGraph("Data/Image/UI/BottonB.png",
		4, 4, 1, 64, 64, &bBottonImage_[0][0], true);

	animCnt_ = 0;

}

void TitleScene::Update(void)
{
	InputManager& ins = InputManager::GetInstance();
	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME);
	}
}

void TitleScene::Draw(void)
{
	animCnt_++;
	DrawFormatString(100, 100, 0xff0000, "Title");

	DrawGraph(0, 0, titleImage_, true);

	DrawRotaGraph(Application::SCREEN_SIZE_X / 2, 400, 0.8, 0.0, gameStartImage_, true);

	DrawRotaGraph(670, 400, 1.0, 0.0, bBottonImage_[(animCnt_ / 10) % 4 - 1][1], true);


}

void TitleScene::Release(void)
{

}