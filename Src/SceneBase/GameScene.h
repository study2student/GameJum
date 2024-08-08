#pragma once
#include "SceneBase.h"

class Enemy;


class Player;
class BulletGimmick;

class GameScene : public SceneBase
{
public:
	static constexpr int GAME_PLAYER_NUM = 2;

	// �R���X�g���N�^
	GameScene(void);

	// �f�X�g���N�^
	~GameScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;
private:

	// �e�̃M�~�b�N
	BulletGimmick* bulletGimmick_;

	// Enemy�p�|�C���^
	Enemy* enemy_;

	// �v���C���[�N���X�̃|�C���^
	Player* player_[GAME_PLAYER_NUM];

};

