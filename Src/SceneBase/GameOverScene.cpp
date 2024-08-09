#include "../Application.h"
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
	gameOverImage_ = LoadGraph("Data/Image/UI/GameOverBack.png");

	first_ = LoadGraph("Data/Image/UI/1st.png");
	second_ = LoadGraph("Data/Image/UI/2nd.png");

	LoadDivGraph("Data/Image/UI/BottonB.png",
		4, 4, 1, 64, 64, &bBottonImage_[0][0], true);

	animCnt_ = 0;
	SetFontSize(60);

	LoadSounds();

	// bgm�����ʂōĐ�
	PlaySoundMem(bgm_, DX_PLAYTYPE_LOOP);
	ChangeVolumeSoundMem(170, bgm_);
}

void GameOverScene::Update(void)
{
	InputManager& ins = InputManager::GetInstance();
	if (ins.IsTrgDown(KEY_INPUT_SPACE) || static_cast<bool>(GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_B))
	{
		StopSoundMem(bgm_, 0);
		PlaySounds(selectSound_,200);
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::TITLE);
	}

}

void GameOverScene::Draw(void)
{

	DrawFormatString(100, 100, 0xff0000, "Result");

	DrawGraph(0, 0, gameOverImage_, true);

	float p1AliveTime = SceneManager::GetInstance().GetAliveTimeP1();
	float p2AliveTime = SceneManager::GetInstance().GetAliveTimeP2();

	DrawFormatString(500, 200, 0x000000, "%.2f", SceneManager::GetInstance().GetAliveTimeP1());
	DrawFormatString(500, 300, 0x000000, "%.2f", SceneManager::GetInstance().GetAliveTimeP2());

	DrawRotaGraph(800, 400, 1.0, 0.0, bBottonImage_[(animCnt_ / 10) % 4 - 1][1], true);

	if (p1AliveTime > p2AliveTime)
	{
		DrawRotaGraph(400, 230, 0.4, 0.0, first_, true);
		DrawRotaGraph(400, 330, 0.4, 0.0, second_, true);
	}
	else if (p1AliveTime < p2AliveTime)
	{
		DrawRotaGraph(400, 230, 0.4, 0.0, second_, true);
		DrawRotaGraph(400, 330, 0.4, 0.0, first_, true);
	}
	else if (p1AliveTime == p2AliveTime)
	{
		DrawRotaGraph(400, 230, 0.4, 0.0, first_, true);
		DrawRotaGraph(400, 330, 0.4, 0.0, first_, true);
	}


	animCnt_++;

}

void GameOverScene::Release(void)
{
	DeleteSoundMem(selectSound_);
	DeleteSoundMem(bgm_);
}

// �ǂݍ��ݗp
bool GameOverScene::LoadSounds(void)
{
	std::string basePath = Application::PATH_SOUNDS;

	bgm_ = LoadSoundMem((basePath + "Rezalt.mp3").c_str());
	selectSound_ = LoadSoundMem((basePath + "Select.mp3").c_str());

	return true;
}

//���̍Đ�
void GameOverScene::PlaySounds(int SoundName, int Vol)
{
	// �����Đ����łȂ���΍Đ��J�n
	if (!(CheckSounds(SoundName)))
	{
		ChangeVolumeSoundMem(Vol, SoundName);
		PlaySoundMem(SoundName, DX_PLAYTYPE_BACK);
	}// �Đ����I��������m�F����
}

// �����Đ������ǂ������f����p
bool GameOverScene::CheckSounds(int SoundName)
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