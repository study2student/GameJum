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

	titleLogoImage_ = LoadGraph("Data/Image/UI/TitleLogo.png");

	animCnt_ = 0;

	LoadSounds();

	// bgm�����ʂōĐ�
	PlaySoundMem(bgm_, DX_PLAYTYPE_LOOP);
	ChangeVolumeSoundMem(170, bgm_);

}

void TitleScene::Update(void)
{
	InputManager& ins = InputManager::GetInstance();
	if (ins.IsTrgDown(KEY_INPUT_SPACE) || static_cast<bool>(GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_B))
	{
		StopSoundMem(bgm_,0);
		PlaySounds(selectSound_, 200);
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

	DrawRotaGraph(Application::SCREEN_SIZE_X / 2, 200, 1.0, 0.0, titleLogoImage_, true);

}

void TitleScene::Release(void)
{
	DeleteSoundMem(selectSound_);
	DeleteSoundMem(bgm_);
}

// �ǂݍ��ݗp
bool TitleScene::LoadSounds(void)
{
	std::string basePath = Application::PATH_SOUNDS;

	bgm_ = LoadSoundMem((basePath + "Title.mp3").c_str());
	selectSound_ = LoadSoundMem((basePath + "Select.mp3").c_str());

	return true;
}

//���̍Đ�
void TitleScene::PlaySounds(int SoundName, int Vol)
{
	// �����Đ����łȂ���΍Đ��J�n
	if (!(CheckSounds(SoundName)))
	{
		ChangeVolumeSoundMem(Vol, SoundName);
		PlaySoundMem(SoundName, DX_PLAYTYPE_BACK);
	}// �Đ����I��������m�F����
}

// �����Đ������ǂ������f����p
bool TitleScene::CheckSounds(int SoundName)
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