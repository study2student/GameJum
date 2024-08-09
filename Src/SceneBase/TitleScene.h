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

private:

	// �^�C�g���w�i
	int titleImage_;

	// �Q�[���X�^�[�g
	int gameStartImage_;

	// B�{�^��
	int bBottonImage_[4][1];

	// �A�j���[�V�����J�E���^
	int animCnt_;

};

