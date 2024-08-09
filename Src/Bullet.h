#pragma once
#include <vector>
#include "Common/Vector2F.h"

class Bullet
{

public:
	struct BulletData
	{
		// ���W
		Vector2F pos;

		// �����t���O
		bool isAlive;
	};

	enum STATE
	{
		NONE,
		SHOT,
		BLAST,
		END
	};

	static constexpr int BULLET_IMAGE_NUM = 4;
	static constexpr int BLAST_IMAGE_NUM = 6;

	static constexpr int BULLET_IMAGE_X_NUM = 4;
	static constexpr int BLAST_IMAGE_X_NUM = 6;

	static constexpr int BULLET_IMAGE_Y_NUM = 1;
	static constexpr int BLAST_IMAGE_Y_NUM = 1;

	static constexpr int BULLET_IMAGE_X_SIZE = 48;
	static constexpr int BLAST_IMAGE_X_SIZE = 16;

	static constexpr int BULLET_IMAGE_Y_SIZE = 32;
	static constexpr int BLAST_IMAGE_Y_SIZE = 16;

	Bullet(void);

	~Bullet(void);

	void Init(void);

	void Update(void);

	void Draw(void);

	void Release(void);

	BulletData GetBulletData(void);

	void CreateShot(void);

	void ChangeState(STATE state);

	STATE GetState(void);

private:

	// �e�̃f�[�^
	BulletData bulletData_;

	// �A�j���[�V�����J�E���^
	int animCnt_;

	// �e�摜
	int bulletImage_[BULLET_IMAGE_X_NUM][BULLET_IMAGE_Y_NUM];

	// �����摜
	int blastImage_[BLAST_IMAGE_X_NUM][BLAST_IMAGE_Y_NUM];

	int blastIdxAnim_;

	// �����̃A�j���[�V�������x
	int blastSpeedAnim_;

	STATE state_;

	void NoneUpdate(void);
	void NoneDraw(void);

	void ShotUpdate(void);
	void ShotDraw(void);

	void BlastUpdate(void);
	void BlastDraw(void);

	void EndUpdate(void);
	void EndDraw(void);

};

