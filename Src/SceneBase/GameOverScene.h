#pragma once
#include "SceneBase.h"
class GameOverScene : public SceneBase
{

public:

	// �R���X�g���N�^
	GameOverScene(void);

	// �f�X�g���N�^
	~GameOverScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

	// �T�E���h�p�֐�-----------------------------------------
	// �ǂݍ��񂾉����Đ�����p
	void PlaySounds(int SoundName, int Vol);

	// �ǂݍ��ݗp
	bool LoadSounds(void);

	// �����Đ������ǂ������f����p
	bool CheckSounds(int SoundName);

private:

	// �Q�[���I�[�o�[�w�i
	int gameOverImage_;

	// B�{�^��
	int bBottonImage_[4][1];

	// �A�j���[�V�����J�E���^
	int animCnt_;

	// 1��
	int first_;

	// 2��
	int second_;

	//BGM
	int bgm_;
	int selectSound_;

};