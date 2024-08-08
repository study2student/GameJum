#pragma once
#include "SceneBase.h"
class Enemy;
class Vector2;
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

	// ��������
	float aliveTimeP1_;
	float aliveTimeP2_;

	// �Փ˔���
	void GimmickCollision(void);

	// �Փ˔���
	bool IsCollisionRect(Vector2 stPos1, Vector2 edPos1, Vector2 stPos2, Vector2 edPos2);

	// �Փ˔���
	bool IsCollisionRectCenter(Vector2 centerPos1, Vector2 size1, Vector2 centerPos2, Vector2 size2);

};

