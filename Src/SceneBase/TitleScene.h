#pragma once

#include "SceneBase.h"
class TitleScene : public SceneBase
{

public:
	// �R���X�g���N�^
	TitleScene(void);

	// �f�X�g���N�^
	~TitleScene(void);

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

	// �^�C�g���w�i
	int titleImage_;

	// �^�C�g�����S
	int titleLogoImage_;

	// �Q�[���X�^�[�g
	int gameStartImage_;

	// B�{�^��
	int bBottonImage_[4][1];

	// �A�j���[�V�����J�E���^
	int animCnt_;

#pragma region ���֘A
	int bgm_;
	int selectSound_;
#pragma endregion

};

