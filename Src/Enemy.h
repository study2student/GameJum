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

	// �Փˍ��W�i���E�j
	enum class COL_LR
	{
		C, // ����
		L, // ��
		R  // �E
	};

	// �Փˍ��W�i�㉺�j
	enum class COL_TD
	{
		C, // ����
		T, // ��
		D  // ��
	};

	Enemy(void);

	~Enemy(void);

	void Init(void);		// ����������

	void Update(void);		// �X�V����

	void Draw(void);		// �`�揈��
		
	void Release(void);		// �������

	void EnemyDraw(void);	// �G�̕`��
	void BulletDraw(void);	// �e�̕`��

	// �ړ�����
	void Move(void);
	void Walk(void);		// �ړ������i�����j
	void Run(void);			// �ړ������i����j

	//�����蔻��
	void CollisionRight(void);
	void CollisionLeft(void);

	// ���ˏ���
	void Shot(void);

	// �f�o�b�O�p
	void Debug(void);		// �L�[����������Ə�Ԑ؂�ւ�
	void DrawDebug(void);	// DrawString�܂Ƃ�

private:

	// �L�����p-------------------------------------------------------------------
	
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

	// �e--------------------------------------------------------------

	// �e�̉摜
	int imgBullet_;

	// �e�̃X�s�[�h
	float speed;

	// �e�̔��a
	float bulletRadius;

	// �e�̍��W
	Vector2 bulletPos_;

	// �e�����������ǂ���
	bool isBullet_;

	// -------------------------------------------------------------------

	// �����蔻��p-------------------------------------------------------
	
	// �Փ˔���p�F���S���W�ipos_����̑��΍��W�j
	Vector2 hitPos_;

	// �Փ˔���p�F�͈�
	Vector2 hitBox_;

	// ���̏Փ˔���
	void CollisionHead(void);

	// ���E�̏Փ˔���
	void CollisionSide(void);

	// �Փˍ��W���擾����
	Vector2 GetColPos(COL_LR lr, COL_TD td);

	// �����_���ɏ�Ԃ��؂�ւ��
	void RandState(void);

	// �o�ߎ��Ԃ�Ԃ�
	int GetTime(void);

	int blink_;
	int rand_;

	bool stateRand_;

	int startTime;
	int elapsedTime;
};

