#pragma once
#include "SceneBase.h"
class Enemy;
class Vector2;
class Player;
class BulletGimmick;
class Stage;

class GameScene : public SceneBase
{
public:
	static constexpr int BG_SIZE = 1047;

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

	// �X�e�[�W�Ƃ̏Փ˔���
	void StageCollision(void);

	// �G�{�̂̓����蔻��
	void EnemyCollision(void);
	// �߂Â�����e�𔭎˂���p�̓����蔻��
	void ShotCollision(void);
	// �e�̓����蔻��
	void BulletCollision(void);

	// �Փ˔���
	bool IsCollisionRect(Vector2 stPos1, Vector2 edPos1, Vector2 stPos2, Vector2 edPos2);

	// �Փ˔���
	bool IsCollisionRectCenter(Vector2 centerPos1, Vector2 size1, Vector2 centerPos2, Vector2 size2);

	// �T�E���h�p�֐�-----------------------------------------
	// �ǂݍ��񂾉����Đ�����p
	void PlaySounds(int SoundName, int Vol);

	// �ǂݍ��ݗp
	bool LoadSounds(void);			

	// �����Đ������ǂ������f����p
	bool CheckSounds(int SoundName);

	//�T�E���h�p�ϐ�-------------------------------------------
	int bgm_;
	int enemyShotSound_;

	//�X�e�[�W
	Stage* stage_;

	// �w�i�֘A
	int bgImage;			// �O���t�B�b�N�n���h��
	int bgPosX1;			// 1���ڂ̔w�i
	int bgPosX2;			// 2���ڂ̔w�i
	int bgSizeX;			// �w�i�̏c�T�C�Y
};

