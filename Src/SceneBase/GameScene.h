#pragma once
#include "SceneBase.h"

class Enemy;


class Player;
class BulletGimmick;

class GameScene : public SceneBase
{
public:
	// �R���X�g���N�^
	GameScene(void);

	// �f�X�g���N�^
	~GameScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;

private:

	std::shared_ptr<Player> player_;

	// �e�̃M�~�b�N
	BulletGimmick* bulletGimmick_;


private:

	// Enemy�p�|�C���^
	Enemy* enemy_;
};

