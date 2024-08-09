#pragma once

#include "Common/Vector2.h"
#include "Common/Vector2F.h"

class Player;
class GameScene;

class Enemy
{
public:
	// �摜�T�C�Y
	static constexpr int SIZE_X = 24;
	static constexpr int SIZE_Y = 24;

	// �����蔻��p�T�C�Y
	static constexpr int HITBOX_X = 24;
	static constexpr int HITBOX_Y = 24;	
	
	// �e���˗p�̓����蔻��T�C�Y
	static constexpr int BULETTBOX_X = 34;
	static constexpr int BULETTBOX_Y = SIZE_Y + 275;

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

	void Init(GameScene* scene_);		// ����������

	void Update(void);		// �X�V����

	void Draw(void);		// �`�揈��
		
	void Release(void);		// �������

	void EnemyDraw(void);	// �G�̕`��
	void BulletDraw(void);	// �e�̕`��

	// �ړ�����
	void Move(void);
	void Walk(void);		// �ړ������i�����j
	void Run(void);			// �ړ������i����j

	
	// ���ˏ���
	void ShotActive(void);
	void Shot(void);
	void ClearBullet(void);

	// �G��Pos
	Vector2F GetEnemyPos(void);
	void SetEnemyPos(Vector2F value);	
	
	// �e��Pow
	Vector2 GetBulletPow(void);
	
	// �e��Pos
	Vector2 GetBulletPos(void);
	void SetBulletPos(Vector2F value);

	// �f�o�b�O�p
	void Debug(void);		// �L�[����������Ə�Ԑ؂�ւ�
	void DrawDebug(void);	// DrawString�܂Ƃ�

private:
	GameScene* gameScene_;
	Player* player1_;
	Player* player2_;

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

	// �e�̈ړ���
	Vector2 bulletPow_;

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

	// �Փˍ��W���擾����
	Vector2 GetColPos(COL_LR lr, COL_TD td);

	// �����_���ɏ�Ԃ��؂�ւ��
	void RandState(void);

	// �o�ߎ��Ԃ�Ԃ�
	int GetTime(void);

	// �����_���p�ϐ�
	int blink_;
	int rand_;

	bool stateRand_;

	// �o�ߎ��Ԏ擾�p�ϐ�
	int startTime;
	int elapsedTime;
};

