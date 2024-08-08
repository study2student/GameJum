#pragma once
#include "../Common/Vector2.h"
#include "../Utility/AsoUtility.h"

class GameScene;

class Player
{
public:
	// �������Ƃ̃A�j���[�V������
	static constexpr int MAX_NUM_ANIM = 15;

	static constexpr int SIZE_X = 153;
	static constexpr int SIZE_Y = 142;

	// �ړ����x
	static constexpr int SPEED_DEFAULT = 5;

	// �A�j���[�V�����X�s�[�h
	static constexpr float ANIM_SPEED = 0.1f;

	// �ړ����x�̍ő�l
	static constexpr float MAX_MOVE_SPEED = 3.5f;

	// ����(accelerator=�A�N�Z�����[�^�[)
	static constexpr float MOVE_ACC = 0.25f;

	// ����(decelarate=�f�B�Z�����C�g)
	static constexpr float MOVE_DEC = 0.05f;

	// �ő�W�����v��
	static constexpr float MAX_JUMP_POW = 8.5f;

	// �ő�̗�
	static constexpr int MAX_HP = 3;

	// �d��
	static constexpr float GRAVITY = 0.25f;

	//	�W�����v�L�[���͂��󂯕t����t���[����
	static constexpr int INPUT_JUMP_FRAME = 6;

	//	�e���ˌ�̍d������
	static constexpr float SHOT_DELAY = 1.0f;

	// �A�j���[�V�������
	enum  class ANIM_STATE
	{
		IDLE,
		RUN,
		JUMP,
		DAMAGED,
		MAX
	};

	// �U�����
	enum  class ATK_STATE
	{
		NONE,
		SHOT,
		MAX
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

	// �v���C���[���
	enum class TYPE
	{
		PLAYER_1,
		PLAYER_2
	};

	// �L�[�R���t�B�O
	struct  KEY_CONFIG
	{
		int UP;
		int DOWN;
		int LEFT;
		int RIGHT;
		int ATTAK;
		int JUMP;
	};

	enum class JoypadButton {
		UP = PAD_INPUT_UP,
		DOWN = PAD_INPUT_DOWN,
		LEFT = PAD_INPUT_LEFT,
		RIGHT = PAD_INPUT_RIGHT,
		ACTION = PAD_INPUT_6
	};

	// �v���C���[���Ƃ̓��̓}�b�s���O
	struct PlayerInput {
		int padId;
		JoypadButton up;
		JoypadButton down;
		JoypadButton left;
		JoypadButton right;
		JoypadButton action;
	};

	// �R���X�g���N�^
	Player(void);

	// �f�X�g���N�^
	~Player(void);

	void Init(GameScene* scene_, TYPE type, KEY_CONFIG config);
	void Update(void);
	void Draw(void);
	void Release(void);

	// �_���[�W��^���鏈��
	void Damage(int damage);

	// �̗͕`��
	void DrawHP(int playerNum);

	// HP�̎擾�i�Q�b�^�[�j
	int GetHp_(void);

	// ���W�̎擾(�Q�b�^�[)
	Vector2F GetPos(void);

	// ��������i�Q�b�^�[�j
	bool IsAlive_(void);

private:


	// �Q�[���V�[���̃|�C���^�ϐ�
	GameScene* gameScene_;

	// �摜�m�����n�m�A�j���[�V�����n
	int images_[static_cast<int>(ANIM_STATE::MAX)]
		[static_cast<int>(ATK_STATE::MAX)][MAX_NUM_ANIM];

	// ���W
	Vector2F pos_;

	// �A�j���[�V�������
	ANIM_STATE animState_;

	// �U�����
	ATK_STATE atkState_;

	// �A�j���[�V�����J�E���^
	float stepAnim_;

	// �v���C���[�̌���
	AsoUtility::DIR dir_;

	// �ړ����x
	float moveSpeed_;

	// �W�����v��
	float jumpPow_;

	// �W�����v������
	bool isJump_;

	// �W�����v
	bool isPutJumpKey_;

	// �W�����v�L�[���̓J�E���^
	int cntJumpInput_;

	// �̗�
	int hp_;

	// �̗͉摜
	int imgHp_;

	// �Փ˔���p�F���S���W�ipos_����̑��΍��W�j
	Vector2 hitPos_;

	// �Փ˔���p�F�͈�
	Vector2 hitBox_;

	// �v���C���[���(1P or 2P)
	TYPE type_;

	// �L�[�ݒ�
	KEY_CONFIG keyConfig_;

	// �e�摜
	int imgShot_;

	// �e���ˌ�̍d������
	float stepShotDelay_;

	// �摜�̓ǂݍ���
	void LoadImages(void);

	// �v���C���[�̕`��
	void DrawPlayer(int handleId);

	// �f�o�b�O�p�̕`��
	void DrawDebug(void);

	// �v���C���[�̈ړ�����
	void ProcessMove(void);

	// �ړ�����
	void Move(void);

	// ����
	void Accele(float speed);

	// �����i�X�s�[�h������������j
	void Decelerate(float speed);

	// �d�͂�������
	void AddGravity(void);

	// �v���C���[�̃W�����v����
	void ProcessJump(void);

	// �W�����v
	void Jump(void);

	// �W�����v�͂̐ݒ�
	void SetJumpPow(float pow);

	// �����̏Փ˔���
	void CollisionFoot(void);

	// ���̏Փ˔���
	void CollisionHead(void);

	// ���E�̏Փ˔���
	void CollisionSide(void);

	// �Փˍ��W���擾����
	Vector2 GetColPos(COL_LR lr, COL_TD td);

	// �U������
	void Attack(void);


};

