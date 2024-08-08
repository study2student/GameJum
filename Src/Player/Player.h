#pragma once
#include "../Common/Vector2.h"

class Player
{
public:
	// �U�����
	enum  class ATK_STATE
	{
		NONE,
		SHOT,
		MAX
	};

	// �R���X�g���N�^
	Player(void);

	// �f�X�g���N�^
	~Player(void);

	void Init();
	void Update(void);
	void Draw(void);
	void Release(void);

private:
	//�v���C���[�摜
	int images;
};