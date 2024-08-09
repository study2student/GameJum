#include <string>
#include <DxLib.h>
#include "../Application.h"
#include "../Manager/SceneManager.h"
#include "../Utility/AsoUtility.h"
#include "../Common/Vector2.h"
#include "../Manager/InputManager.h"
#include "../SceneBase/GameScene.h"
#include "../Stage/Stage.h"
#include "Player.h"


Player::Player(void)
{
}

Player::~Player(void)
{
}

void Player::Init(GameScene* scene_, TYPE type, KEY_CONFIG config, PAD_CONFIG padConfig, InputManager::JOYPAD_NO padID)
{
	gameScene_ = scene_;

	// �v���C���[���
	type_ = type;

	// �L�[�ݒ�
	keyConfig_ = config;

	// �p�b�h�ݒ�
	padConfig_ = padConfig;

	padID_ = padID;

	// �摜�̓ǂݍ���
	LoadImages();

	// �A�j���[�V�������
	animState_ = ANIM_STATE::RUN;

	// �U�����
	atkState_ = ATK_STATE::NONE;

	// �A�j���[�V�����J�E���^
	stepAnim_ = 0;

	// �������W
	pos_ = { 300.0f, 350.0f };
	if (type_ == TYPE::PLAYER_2)
	{
		pos_ = { 500.0f, 350.0f };
	}

	// �v���C���[����
	dir_ = AsoUtility::DIR::LEFT;
	if (type_ == TYPE::PLAYER_2)
	{
		dir_ = AsoUtility::DIR::RIGHT;
	}

	// �ړ����x�̏�����
	moveSpeed_ = 0.0f;

	// �W�����v��
	jumpPow_ = 0.0f;

	// �W�����v����
	isJump_ = true;

	// �W�����v�L�[���̓J�E���^
	// �X�^�[�g�����1�񒅒n���Ȃ��ƃW�����v�ł��Ȃ�
	cntJumpInput_ = INPUT_JUMP_FRAME;

	// �W�����v�L�[��������
	isPutJumpKey_ = false;

	// �Փ˔���p�F���S���W�ipos_����̑��΍��W�j
	hitPos_ = { 0, 8 };

	// �Փ˔���p�F�͈�
	hitBox_ = { 16, 46};

	// �V���b�g�̍d������
	stepShotDelay_ = 0.0f;

	//�̗�
	hp_ = MAX_HP;
}

void Player::Update(void)
{
	// ���[�V�����̏�����
	animState_ = ANIM_STATE::IDLE;

	// �v���C���[�̈ړ�����
	ProcessMove();

	// ����
	Decelerate(MOVE_DEC);

	// �ړ�����
	Move();

	// ���E�̏Փ˔���
	//CollisionSide();

	// �v���C���[�̃W�����v����
	ProcessJump();

	// �d�͂���ɂ�����
	AddGravity();

	// �W�����v
	Jump();

	// �����̏Փ˔���
	CollisionFoot();

	// ���̏Փ˔���
	//CollisionHead();


	// �U��
	Attack();
}

void Player::Draw(void)
{
	DrawDebug();

	// ���W�ϊ�
	Vector2 pos = pos_.ToVector2();

	if (isJump_)
	{
		animState_ = ANIM_STATE::JUMP;
	}

	// �A�j���[�V�������
	int animState = static_cast<int>(animState_);

	// �U�����
	int atkState = static_cast<int>(atkState_);

	switch (animState_)
	{
	case ANIM_STATE::IDLE:
	{
		stepAnim_ += ANIM_SPEED;
		int animIdxIdle = AsoUtility::Round(stepAnim_) % MAX_NUM_ANIM;
		DrawPlayer(images_[animState][atkState][animIdxIdle]);
	}
	case ANIM_STATE::JUMP:
	{
		stepAnim_ += ANIM_SPEED;
		int animIdx = AsoUtility::Round(stepAnim_) % MAX_NUM_ANIM;
		DrawPlayer(images_[animState][atkState][animIdx]);
	}
	break;
	case ANIM_STATE::RUN:
	{
		stepAnim_ += ANIM_SPEED;
		int animIdx = AsoUtility::Round(stepAnim_) % MAX_NUM_ANIM;
		DrawPlayer(images_[animState][atkState][animIdx]);
	}
	break;
	case ANIM_STATE::DAMAGED:
		DrawPlayer(images_[animState][0][0]);
		break;
	}

}

void Player::Release(void)
{

	int animMax = static_cast<int>(ANIM_STATE::MAX);
	int atkMax = static_cast<int>(ATK_STATE::MAX);
	int animNumMax = MAX_NUM_ANIM;
	for (int m = 0; m < animMax; m++)
	{
		for (int k = 0; k < atkMax; k++)
		{
			for (int n = 0; n < animNumMax; n++)
			{
				DeleteGraph(images_[m][k][n]);
			}
		}
	}

	// �e�摜�̉��
	DeleteGraph(imgShot_);

}

void Player::Damage(int damage)
{
	hp_ -= damage;
}

int Player::GetHp_(void)
{
	return hp_;
}

Vector2F Player::GetPos(void)
{
	return pos_;
}

bool Player::IsAlive_(void)
{
	return false;
}

void Player::LoadImages(void)
{
	std::string basePath = Application::PATH_IMAGE;

	if (type_ == TYPE::PLAYER_2)
	{
		basePath = Application::PATH_IMAGE;
	}


	int anim = 0;
	int atkNone = static_cast<int>(ATK_STATE::NONE);
	int atkShot = static_cast<int>(ATK_STATE::SHOT);

	// �ҋ@���[�V����
	anim = static_cast<int>(ANIM_STATE::IDLE);

	//images_[anim][atkNone][0] = LoadGraph((basePath + "Player/Idle.png").c_str());
	LoadDivGraph(
		(basePath + "Player/Idle.png").c_str(),
		MAX_NUM_ANIM,
		MAX_NUM_ANIM, 1,
		SIZE_X, SIZE_Y,
		&images_[anim][atkNone][0],
		false);

	images_[anim][atkShot][0] = LoadGraph((basePath + "Player/IdleShot.png").c_str());

	// �W�����v
	anim = static_cast<int>(ANIM_STATE::JUMP);
	//images_[anim][atkNone][0] = LoadGraph((basePath + "Player/Jump.png").c_str());
	LoadDivGraph(
		(basePath + "Player/Jump.png").c_str(),
		MAX_NUM_ANIM,
		MAX_NUM_ANIM, 1,
		SIZE_X, SIZE_Y,
		&images_[anim][atkNone][0],
		false);

	// ��_���[�W
	anim = static_cast<int>(ANIM_STATE::DAMAGED);
	images_[anim][atkNone][0] = LoadGraph((basePath + "Player/Damaged.png").c_str());

	// ����
	anim = static_cast<int>(ANIM_STATE::RUN);

	//P1
	LoadDivGraph(
		(basePath + "Player/Run.png").c_str(),
		MAX_NUM_ANIM,
		MAX_NUM_ANIM, 1,
		SIZE_X, SIZE_Y,
		&images_[anim][atkNone][0],
		false);

	// �e�摜
	imgShot_ = LoadGraph((basePath + "Shot.png").c_str());

	// �̗͉摜
	imgHp_ = LoadGraph((basePath + "Player/Heart.png").c_str());
}

void Player::DrawPlayer(int handleId)
{

	// ���W�ϊ�
	Vector2 pos = pos_.ToVector2();

	// �v���C���[�̌���
	bool isLeftDir = true;
	if (dir_ == AsoUtility::DIR::RIGHT)
	{
		isLeftDir = false;
	}

	// �`��(���W�A�g�嗦�A��]�A�n���h��ID�A���߃t���O�A�����]�A�c���])
	DrawRotaGraph(
		pos.x, pos.y,
		1.0, 0.0, handleId, true,
		isLeftDir);

}

void Player::DrawDebug(void)
{
	DrawFormatString(0, 0, 0x000000, "�v���C���[���W(%.2f, %.f)", pos_.x, pos_.y);

	DrawFormatString(0, 20, 0x000000, "�ړ����x(%.2f)", moveSpeed_);

	DrawFormatString(0, 40, 0x000000, "�W�����v��(%.2f)", jumpPow_);

	Vector2 pos = pos.ToVector2F();

	DrawBox(pos_.x - SIZE_X / 2, pos_.y - SIZE_Y / 2, pos_.x + SIZE_X / 2, pos_.y + SIZE_Y / 2, 0xffffff, false);

	//DrawBox(pos_.x - SIZE_X / 2, pos_.y - SIZE_Y / 2, pos_.x + SIZE_X / 2, pos_.y + SIZE_Y / 2, 0xffffff, false);

	DrawBox(pos.x - 3, pos.y - 3, pos.x + 3, pos.y + 3, 0xff0000, true);

	// �I�����W
	int color = 0xff8c00;

	// ���̍��W
	Vector2 headPosL = GetColPos(COL_LR::L, COL_TD::T);
	// ���̍��W
	Vector2 corePosL = GetColPos(COL_LR::L, COL_TD::C);
	// �������W�i���j
	Vector2 footPosL = GetColPos(COL_LR::L, COL_TD::D);

	pos = headPosL;
	DrawBox(pos.x - 3, pos.y - 3, pos.x + 3, pos.y + 3, 0xff0000, true);
	pos = corePosL;
	DrawBox(pos.x - 3, pos.y - 3, pos.x + 3, pos.y + 3, 0xff0000, true);
	pos = footPosL;
	DrawBox(pos.x - 3, pos.y - 3, pos.x + 3, pos.y + 3, 0xff0000, true);

	// �E�̍��W
	Vector2 headPosR = GetColPos(COL_LR::R, COL_TD::T);
	// �E�̍��W
	Vector2 corePosR = GetColPos(COL_LR::R, COL_TD::C);
	// �������W�i�E�j
	Vector2 footPosR = GetColPos(COL_LR::R, COL_TD::D);

	pos = headPosR;
	DrawBox(pos.x - 3, pos.y - 3, pos.x + 3, pos.y + 3, 0xff0000, true);
	pos = corePosR;
	DrawBox(pos.x - 3, pos.y - 3, pos.x + 3, pos.y + 3, 0xff0000, true);
	pos = footPosR;
	DrawBox(pos.x - 3, pos.y - 3, pos.x + 3, pos.y + 3, 0xff0000, true);

	// �������W
	Vector2 footPosC = GetColPos(COL_LR::C, COL_TD::D);

	pos = footPosC;
	DrawBox(pos.x - 3, pos.y - 3, pos.x + 3, pos.y + 3, 0xff0000, true);

	// ���̍��W���W
	Vector2 headPosC = GetColPos(COL_LR::C, COL_TD::T);

	pos = headPosC;
	DrawBox(pos.x - 3, pos.y - 3, pos.x + 3, pos.y + 3, 0xff0000, true);

	// �f�o�b�O�p�F�����Փ˔���
	Vector2 footPos = pos;
	footPos.y += (4 + 24);

	// �����F����
	DrawBox(footPos.x - 3, footPos.y - 3, footPos.x + 3, footPos.y + 3, color, true);


	DrawBox(footPos.x - 3 - 16, footPos.y - 3, footPos.x + 3 - 16, footPos.y + 3, color, true);

	// �f�o�b�O�p�F���̏Փ˔���
	Vector2 headPos = pos;
	headPos.y += (8 - 24);

	// ���F����
	DrawBox(headPos.x - 3, headPos.y - 3, headPos.x + 3, headPos.y + 3, color, true);
	DrawBox(headPos.x - 3, headPos.y - 3, headPos.x + 3, headPos.y + 3, color, true);
	DrawBox(headPos.x - 3, headPos.y - 3, headPos.x + 3, headPos.y + 3, color, true);
}

void Player::DrawHP(int playerNum)
{
	int scX = Application::SCREEN_SIZE_X;
	int scY = Application::SCREEN_SIZE_Y;
	for (int i = 0; i <  80 * hp_; i += 80)
	{
		DrawRotaGraphFastF(0 + 35 + i, 35 + 70 * playerNum, 0.1f, 0.0f, imgHp_, true);
	}

}

void Player::ProcessMove(void)
{
	auto& ins = InputManager::GetInstance();

	// ������
	if (ins.IsNew(keyConfig_.LEFT))
	{
		animState_ = ANIM_STATE::RUN;

		dir_ = AsoUtility::DIR::LEFT;
		// ����
		Accele(-MOVE_ACC);
	}

	if (ins.InputManager::GetJPadInputState(padID_).AKeyLX) {
		animState_ = ANIM_STATE::RUN;
		dir_ = AsoUtility::DIR::LEFT;
		Accele(-MOVE_ACC);
	}


	// �E����
	if (ins.IsNew(keyConfig_.RIGHT))
	{
		animState_ = ANIM_STATE::RUN;

		dir_ = AsoUtility::DIR::RIGHT;
		// ����
		Accele(MOVE_ACC);
	}

	if (ins.InputManager::GetJPadInputState(padID_).AKeyRX)
	{
		animState_ = ANIM_STATE::RUN;

		dir_ = AsoUtility::DIR::RIGHT;
		// ����
		Accele(MOVE_ACC);
	}
}

void Player::Move(void)
{
	pos_.x += moveSpeed_;
}

void Player::Accele(float speed)
{  
	moveSpeed_ += speed;

	// ���x����(�E����)
	if (moveSpeed_ > MAX_MOVE_SPEED)
	{
		moveSpeed_ = MAX_MOVE_SPEED;
	}

	// ���x����(������)
	if (moveSpeed_ < -MAX_MOVE_SPEED)
	{
		moveSpeed_ = -MAX_MOVE_SPEED;
	}

}

void Player::Decelerate(float speed)
{

	// �E�����̈ړ�������������
	if (moveSpeed_ > 0.0f)
	{
		moveSpeed_ -= speed;
		if (moveSpeed_ < 0.0f)
		{
			moveSpeed_ = 0.0f;
		}
	}

	// �������̈ړ�������������
	if (moveSpeed_ < 0.0f)
	{
		moveSpeed_ += speed;
		if (moveSpeed_ > 0.0f)
		{
			moveSpeed_ = 0.0f;
		}
	}
}

void Player::ProcessJump(void)
{

	// �P���W�����v
	//if (InputManager::GetInstance().IsNew(KEY_INPUT_M) && !isJump_)
	//{
	//	SetJumpPow(-MAX_JUMP_POW);
	//	isJump_ = true;
	//}
	auto& ins = InputManager::GetInstance();

	// �ڒn���ĂȂ��ƁA�W�����v���J�n�ł��Ȃ��悤�ɂ���
	if ((ins.IsTrgDown(keyConfig_.JUMP) 
		|| ins.IsPadBtnTrgDown(padID_, InputManager::JOYPAD_BTN::RIGHT))
		&& !isJump_)
	{
		isJump_ = true;
		isPutJumpKey_ = true;
	}
	if (static_cast<bool>(GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_A) && !isJump_)
	{
		isJump_ = true;
		isPutJumpKey_ = true;
	}
	// ���͎��Ԃɉ����ăW�����v�ʂ�ύX����
	if (ins.IsNew(keyConfig_.JUMP) 
		&& ins.IsPadBtnNew(padID_, InputManager::JOYPAD_BTN::RIGHT)
		&& cntJumpInput_ < INPUT_JUMP_FRAME
		&& isPutJumpKey_)
	{
		// �W�����v�J�E���^�𑝂₷
		cntJumpInput_++;

		//�Ӗ����Ȃ�
		//SetJumpPow(-MAX_JUMP_POW);

		// ���Z�͂ł������W�����v�͂��傫������
		//float pow = jumpPow_ - MAX_JUMP_POW;
		//SetJumpPow(pow);

		// 
		float pow = jumpPow_ - (MAX_JUMP_POW / static_cast<float>(INPUT_JUMP_FRAME));
		SetJumpPow(pow);

	}

	// 2�i�W�����v���֎~����
	if (ins.IsTrgUp(keyConfig_.JUMP))
	{
		// �W�����v�{�^���𗣂��ꂽ��
		cntJumpInput_ = INPUT_JUMP_FRAME;
	}

}

void Player::Jump(void)
{
	pos_.y += jumpPow_;

	//// ���̐ڒn�i�Փˁj����
	//if (pos_.y > 380.0f)
	//{
	//	pos_.y = 380.0f;

	//	// �n�ʂɂ����̂ŃW�����v�����Z�b�g
	//	isJump_ = false;
	//	SetJumpPow(0.0f);

	//	// �ݒu������
	//	cntJumpInput_ = 0;
	//}
}

void Player::SetJumpPow(float pow)
{
	// �W�����v�͂�ݒ�
	jumpPow_ = pow;

	// �d�͂�������߂���̂�h��
	if (jumpPow_ > MAX_JUMP_POW)
	{
		jumpPow_ = MAX_JUMP_POW;
	}

}

void Player::CollisionFoot(void)
{


	// �������W
	Vector2 s = GetColPos(COL_LR::L, COL_TD::T);
	Vector2 e = GetColPos(COL_LR::R, COL_TD::D);

	if (gameScene_->IsCollisionStage(s, e))
	{
		pos_.y = 363;
		//�n�ʂɂ�����W�����v�����Z�b�g����
		isJump_ = false;
		SetJumpPow(0.0f);
		// �ڒn������W�����v�J�E���^�����ɖ߂�
		cntJumpInput_ = 0;

		// �W�����v�L�[�̉�������
		isPutJumpKey_ = false;
	}




	// �ڒn����i�����̏Փ˔���j

	// �������W
	Vector2 footPosC = GetColPos(COL_LR::C, COL_TD::D);


	// �������W�i���j
	Vector2 footPosL = GetColPos(COL_LR::L, COL_TD::D);

	// �������W�i�E�j
	Vector2 footPosR = GetColPos(COL_LR::R, COL_TD::D);




	//if (gameScene_->IsCollisionStage(footPosC)
	//	|| gameScene_->IsCollisionStage(footPosL)
	//	|| gameScene_->IsCollisionStage(footPosR)
	//	)
	//{
	//	Vector2 mapPos = gameScene_->World2MapPos(footPosC);
	//	pos_.y = static_cast<float>(mapPos.y * Stage::SIZE_Y - 1 - hitBox_.y - hitPos_.y);
	//	// �n�ʂɂ����̂ŃW�����v�����Z�b�g����
	//	isJump_ = false;
	//	SetJumpPow(0.0f);
	//	// �ڒn������W�����v�J�E���^�����ɖ߂�
	//	cntJumpInput_ = 0;

	//	// �W�����v�L�[�̉�������
	//	isPutJumpKey_ = false;
	//}

	//// �󒆔���
	//footPosC.y += 1;
	//footPosL.y += 1;
	//footPosR.y += 1;
	//if (!(gameScene_->IsCollisionStage(footPosC)
	//	|| gameScene_->IsCollisionStage(footPosL)
	//	|| gameScene_->IsCollisionStage(footPosR))
	//	)
	//{
	//	// �ڒn���Ă��Ȃ��̂ŁA�W�����v����ɂ���
	//	isJump_ = true;
	//}
}

void Player::CollisionHead(void)
{
	// ���̏Փ˔���i�����̏Փ˔���j

	// ���̍��W���W
	Vector2 headPosC = GetColPos(COL_LR::C, COL_TD::T);


	// ���̍��W�i���j
	Vector2 headPosL = GetColPos(COL_LR::L, COL_TD::T);


	// ���̍��W�i�E�j
	Vector2 headPosR = GetColPos(COL_LR::R, COL_TD::T);


	//if (gameScene_->IsCollisionStage(headPosC)
	//	|| gameScene_->IsCollisionStage(headPosL)
	//	|| gameScene_->IsCollisionStage(headPosR)
	//	)
	//{
	//	Vector2 mapPos = gameScene_->World2MapPos(headPosC);
	//	pos_.y = static_cast<float>(mapPos.y * Stage::SIZE_Y + Stage::SIZE_Y + SIZE_Y / 2 + hitPos_.y - hitBox_.y);

	//	SetJumpPow(0.0f);
	//}

}

void Player::CollisionSide(void)
{
	//// ���E�̏Փ˔���i���E�̏Փ˔���j

	//// ���̍��W
	//Vector2 headPosL = GetColPos(COL_LR::L, COL_TD::T);
	//// ���̍��W
	//Vector2 corePosL = GetColPos(COL_LR::L, COL_TD::C);
	//// �������W�i���j
	//Vector2 footPosL = GetColPos(COL_LR::L, COL_TD::D);

	//if (gameScene_->IsCollisionStage(headPosL)
	//	|| gameScene_->IsCollisionStage(footPosL)
	//	|| gameScene_->IsCollisionStage(corePosL)
	//	)
	//{
	//	Vector2 mapPos = gameScene_->World2MapPos(headPosL);
	//	pos_.x = static_cast<float>(mapPos.x * Stage::SIZE_X
	//		+ Stage::SIZE_X + hitBox_.x);

	//}

	//if (pos_.x > pos_.x + SIZE_X)
	//{
	//	Vector2 mapPos = gameScene_->World2MapPos(headPosL);
	//	pos_.x = static_cast<float>(mapPos.x * Stage::SIZE_X
	//		+ Stage::SIZE_X + hitBox_.x);

	//}


	//// �E�̍��W
	//Vector2 headPosR = GetColPos(COL_LR::R, COL_TD::T);
	//// �E�̍��W
	//Vector2 corePosR = GetColPos(COL_LR::R, COL_TD::C);
	//// �������W�i�E�j
	//Vector2 footPosR = GetColPos(COL_LR::R, COL_TD::D);

	//if (gameScene_->IsCollisionStage(headPosR)
	//	|| gameScene_->IsCollisionStage(footPosR)
	//	|| gameScene_->IsCollisionStage(corePosR)
	//	)
	//{
	//	Vector2 mapPos = gameScene_->World2MapPos(headPosR);
	//	pos_.x = static_cast<float>(mapPos.x * Stage::SIZE_X
	//		- 1 - hitBox_.x);

	//}

	//InputManager& ins = InputManager::GetInstance();
	//if (ins.IsTrgDown(KEY_INPUT_Z))
	//{
	//	hp_--;
	//}
}

Vector2 Player::GetColPos(COL_LR lr, COL_TD td)
{
	Vector2 ret = pos_.ToVector2();

	// ���΍��W�𑫂�
	ret.x += hitPos_.x;
	ret.y += hitPos_.y;

	// ���E
	switch (lr)
	{
	case Player::COL_LR::L:
		ret.x -= hitBox_.x;
		break;
	case Player::COL_LR::R:
		ret.x += hitBox_.x;
		break;
	}

	// �㉺
	switch (td)
	{
	case Player::COL_TD::T:
		ret.y -= hitBox_.y;
		break;
	case Player::COL_TD::D:
		ret.y += hitBox_.y;
		break;
	}

	return ret;
}

void Player::Attack(void)
{
	// �{�^���������ꂽ��e�𐶐�

	// �U���L�[�������ƁA�e�𐶐�
	if (InputManager::GetInstance().IsNew(keyConfig_.ATTAK)
		&& stepShotDelay_ <= 0.0f)
	{
		// �L���ȋ����擾����
		//Shot* shot = GetValidShot();

		// ���b�N�}���̘r�̒��������W�����炷
		Vector2F pos = pos_;

		//if (dir_ == AsoUtility::DIR::RIGHT)
		//{
		//	pos.x += 20.0f;
		//}
		//
		//// 
		//if (dir_ == AsoUtility::DIR::LEFT)
		//{
		//	pos.x -= 20.0f;
		//}

		// �e�𐶐�(�e���˂̏���)
		Vector2F dir = AsoUtility::Normalize(dir_);
		//shot->CreateShot(pos.ToVector2(), dir);

		float powX = 20.0f;
		float movePowX = dir.x * powX;
		pos.x += movePowX;

		if (isJump_)
		{
			pos.y -= 10.0f;
		}
		else
		{
			pos.y += 5.0f;
		}

		// �e�̔��ˌ�̍d�����ԃZ�b�g
		stepShotDelay_ = SHOT_DELAY;
	}


	atkState_ = ATK_STATE::NONE;
	if (stepShotDelay_ > 0.0f)
	{
		// �e���ˌ�̍d�����Ԃ����炷
		//stepShotDelay_ -= 1.0f / SceneManager::DEFAULT_FPS;

		// �e�������Ă���Ԃ́A�U�����Ƃ���
		atkState_ = ATK_STATE::SHOT;
	}
}

//Shot* Player::GetValidShot(void)
//{
//	auto size = shots_.size();
//	for (int i = 0; i < size; i++)
//	{
//		if (!shots_[i]->IsAlive())
//		{
//			// �������Ă��Ȃ��e�Ȃ̂�
//			// ���̃C���X�^���X�����T�C�N��
//			return shots_[i];
//		}
//	}
//
//	// �������Ă��Ȃ��e��������Ȃ�����
//	Shot* shot = new Shot(imgShot_);
//	shots_.push_back(shot);
//
//	return shot;
//}

void Player::AddGravity(void)
{
	// ���݂̃W�����v�͂ɏd�͂�������
	float pow = jumpPow_ + GRAVITY;
	SetJumpPow(pow);
}
