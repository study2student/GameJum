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
	static constexpr int RUN_ANIM_NUM = 6;

	// ���A�j���[�V������
	static constexpr int ANIM_MAX_NUM_X = 6;
	static constexpr int ANIM_MAX_NUM_Y = 5;
	
	// �A�j���[�V�����̏��
	enum class ANIM_STATE
	{
		IDLE,
		WALK,
		KICK,
		HIT,
		RUN,
		MAX
	};

	// �U���̏��
	enum class ATK_STATE
	{
		NONE,
		SHOT,
		MAX
	};

	// ����
	enum class DIR
	{
		RIGHT,
		LEFT
	};

	struct Bullet {
		Vector2 pos;		// ���W
		float angle;
		Vector2 vel;		// ���x
		Vector2 accel;		// ���x
		bool isbullet;		// ���݂��Ă��邩
	};

	Enemy(void);

	~Enemy(void);

	void Init(void);		// ����������

	void Update(void);		// �X�V����

	void Draw(void);		// �`�揈��
		
	void Release(void);		// �������

	void EnemyDraw(void);
	void BulletDraw(void);

	// �ړ�����
	void Walk(void);		// �ړ������i�����j
	void Run(void);			// �ړ������i����j

	// ���ˏ���
	void Shot(void);

	void Debug(void);

private:
	// �摜�i�[�̈�
	int imgsDino_[ANIM_MAX_NUM_Y][ANIM_MAX_NUM_X];

	// �A�j���[�V�����̏��
	ANIM_STATE state_;

	// �U���̏��
	ATK_STATE atkState_;

	// ����
	DIR dir_;

	// ���W
	Vector2F pos_;

	// ���ړ�����ۂ̈ړ���
	float movePow_;

	// �A�j���[�V�����p
	int animNum_;

	// �A�j���[�V�����p�̃J�E���^�[
	int cntAnim_;

	// �A�j���[�V�����X�s�[�h
	float speedAnim_;

	// 
	Bullet bullets[256];

	// �e�̉摜
	int imgBullet_;

	// �e�̃X�s�[�h
	float speed;

	// �e�̔��a
	float bulletRadius;

	Vector2 bulletPos_;

};

