#pragma once
#include <vector>
#include "Common/Vector2F.h"

class BulletGimmick
{

public:

	struct BulletData
	{

		// ���W
		Vector2F pos;

		// �����t���O
		bool isAlive;

	};

	static constexpr int IMAGE_NUM = 4;

	static constexpr int IMAGE_X_NUM = 4;

	static constexpr int IMAGE_Y_NUM = 1;

	static constexpr int IMAGE_X_SIZE = 48;

	static constexpr int IMAGE_Y_SIZE = 32;

	BulletGimmick(void);

	~BulletGimmick(void);

	void Init(void);

	void Update(void);
	
	void Draw(void);

	void Release(void);

	// �e�̃f�[�^�̎擾
	std::vector<BulletData> GetBulletData(void);

private:

	// �e�̃f�[�^
	std::vector<BulletData> bulletData_;

	// �A�j���[�V�����J�E���^
	int animCnt_;

	// �摜
	int image_[IMAGE_X_NUM][IMAGE_Y_NUM];

};