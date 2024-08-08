#pragma once
#include <vector>
#include <string>
#include "../Common/Vector2F.h"

class Stage
{
public:

#pragma region �摜�֘A
	//�摜�T�C�Y
	static constexpr int IMG_SIZE_X = 768;
	static constexpr int IMG_SIZE_Y = 384;

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
	static constexpr int CREATE_MAX = 2;

	//��
	static constexpr int STAGE_SIZE_X_LONG = 24;
	static constexpr int STAGE_SIZE_X_NORMAL = 16;
	static constexpr int STAGE_SIZE_X_MIDDLE = 12;

	//����(�Œ�)
	static constexpr int STAGE_SIZE_Y = 4;

	//��(�������玟�̒n�ʕ`��܂ł̕�)
	static constexpr int HOLE_SIZE_X_ = 4;
#pragma endregion 
	
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
		//��(�c��)
		int row_;

		//�s(����)
		int col_;

		//�X�e�[�W�z��
		std::vector<std::vector<int>> stageChips_;

		//�n�_
		Vector2F pos_;
	};
#pragma endregion 

	Stage();
	~Stage();

	void Init();
	void Update();
	void Draw();
	void Release();

	void Load();
	void Reset();


	//����̕��̐ݒ�
	int SetStageSizeX();

	//CSV�f�[�^�̓ǂݍ���
	void LoadCsvData(int cnt);

	//����������
	void ClearUsedGround(int cnt);

private:

	//�摜�i�[
	int imgStageChip_[DIVISION_ALL_NUM];

	//�`�b�v�p�z��
	int chipNum_[DIVISION_NUM_Y][DIVISION_NUM_X];	
	
	//�n��
	Ground grounds_[CREATE_MAX];

	//�n��CSV�f�[�^
	std::string groundCsv_[static_cast<int>(GROUND_SIZE::MAX)];

};

