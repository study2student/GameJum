#pragma once
#include <vector>
#include <string>
#include "../Common/Vector2F.h"

class Stage
{
public:

#pragma region �n�ʗp�\����
	enum class GROUND_SIZE
	{
		LONG,
		MIDDLE,
		NORMAL,
		MAX
	};

	struct Ground
	{
		//�n�_���W
		Vector2F pos_;
	};
#pragma endregion 

#pragma region �摜�֘A
	//�摜�T�C�Y
	static constexpr int IMG_SIZE_X = 384;
	static constexpr int IMG_SIZE_Y = 192;

	//�摜������
	static constexpr int DIVISION_NUM_X = 12;
	static constexpr int DIVISION_NUM_Y = 6;

	//������̉摜�T�C�Y
	static constexpr int SIZE_X = IMG_SIZE_X / DIVISION_NUM_X;
	static constexpr int SIZE_Y = IMG_SIZE_Y / DIVISION_NUM_Y;

	//��������
	static constexpr int DIVISION_ALL_NUM = DIVISION_NUM_X * DIVISION_NUM_Y;
#pragma endregion 

#pragma region �X�e�[�W�T�C�Y�֘A
	//�n�ʐ�����
	static constexpr int CREATE_MAX = static_cast<int>(GROUND_SIZE::MAX);

	//��
	static constexpr int STAGE_SIZE_X_LONG = 24;
	static constexpr int STAGE_SIZE_X_NORMAL = 16;
	static constexpr int STAGE_SIZE_X_MIDDLE = 12;

	//����(�Œ�)
	static constexpr int STAGE_SIZE_Y = 4;

	//��(�������玟�̒n�ʕ`��܂ł̕�)
	static constexpr int HOLE_SIZE_X_ = 10;
#pragma endregion 

	Stage();
	~Stage();

	void Init();
	void Update();
	void Draw();
	void Release();

	void Load();
	void Reset();

	//CSV�f�̓ǂݍ���
	void LoadCsvData();
	
	//����������
	void ClearUsedGround(int cnt);

	//�|�C���^�̎擾
	std::vector<Ground> GetGround();

private:

	//�摜�i�[
	int imgStageChip_[DIVISION_ALL_NUM];

	//��(�c��)
	int row_;

	//�s(����)
	int col_;

	//�X�e�[�W�}�b�v�`�b�v�z��
	int stageChips_[STAGE_SIZE_Y][STAGE_SIZE_X_LONG];

	//CSV�f�[�^
	std::string csvData_;
	
	//�n��
	std::vector<Ground> grounds_;
};

