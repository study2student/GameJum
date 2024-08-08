#pragma once

#include "Common/Vector2.h"
#include "Common/Vector2F.h"

class Enemy
{
public:
	// �摜�T�C�Y
	static constexpr int SIZE_X = 24;
	static constexpr int SIZE_Y = 24;

	// �A�j���[�V������
	// IDLE
	static constexpr int IDLE_ANIM_NUM = 4;
	// WALK
	static constexpr int WALK_ANIM_NUM = 6;
	// KICK
	static constexpr int KICK_ANIM_NUM = 4;
	// HIT
	static constexpr int HIT_ANIM_NUM = 3;
	// RUN
	static constexpr int RUN_ANIM_NUM = 7;

	// ���A�j���[�V������
	static constexpr int ANIM_MAX_NUM_X = 24;
	static constexpr int ANIM_MAX_NUM_Y = 5;
	
	// ���
	enum class STATE
	{
		IDLE,
		WALK,
		KICK,
		HIT,
		RUN
	};

	Enemy(void);

	~Enemy(void);

	void Init(void);

	void Update(void);

	void Draw(void);

	void Release(void);

private:
	// �摜�i�[�̈�
	int imgsDino_[ANIM_MAX_NUM_Y][ANIM_MAX_NUM_X];

	// ���
	STATE state_;

	// ���W
	Vector2F pos_;

	float movePow_;

	int animNum_;

	// �A�j���[�V�����p�̃J�E���^�[
	int cntAnim_;

	// �A�j���[�V�����X�s�[�h
	float speedAnim_;
};

