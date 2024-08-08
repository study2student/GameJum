#include <DxLib.h>
#include <iostream>
#include <fstream>
#include "../Application.h"
#include "Stage.h"

Stage::Stage()
{
}

Stage::~Stage()
{
}

void Stage::Init()
{	
	Reset();
	
	Load();

	SetFirstStage();
}

void Stage::Update()
{
	for (const auto& ground : grounds_)
	{

	}
}

void Stage::Draw()
{
	for (const auto& ground : grounds_)
	{
		for (int i = 0; i < ground.row_; i++)
		{
			for (int j = 0; j < ground.col_; j++)
			{
				DrawGraph(ground.pos_.x,
					ground.pos_.y,
					ground.stageChips_[i][j],
					true);
			}
		}
	}
}

void Stage::Release()
{
	for (int i = 0; i < DIVISION_ALL_NUM; i++)
	{
		DeleteGraph(imgStageChip_[i]);
	}
}

void Stage::Load()
{
	//�摜�ǂݍ���
	LoadDivGraph("Data/Stage/tileset.png",
		DIVISION_ALL_NUM,
		DIVISION_NUM_X,
		DIVISION_NUM_Y,
		SIZE_X,
		SIZE_Y,
		&(imgStageChip_[0]));
}

void Stage::Reset()
{
	//CSV�f�[�^
	groundCsv_[static_cast<int>(GROUND_SIZE::MIDDLE)] = "Data/MiddleGroundCsvData.csv";
	groundCsv_[static_cast<int>(GROUND_SIZE::NORMAL)] = "Data/NormalGroundCsvData.csv";
	groundCsv_[static_cast<int>(GROUND_SIZE::LONG)] = "Data/LongGroundCsvData.csv";
}

void Stage::SetFirstStage()
{
	for (int i = 0; i < CREATE_MAX; i++)
	{
		//��
		grounds_[i].row_ = STAGE_SIZE_Y;

		//�s
		grounds_[i].col_ = SetStageSizeX();

		//���W
		grounds_[i].pos_ = { i * (SIZE_X + HOLE_SIZE_X_) * DIVISION_NUM_X,
							Application::SCREEN_SIZE_Y - (SIZE_Y * grounds_[i].row_) };

		//�X�e�[�W�`�b�v�̐ݒ�
		//�v�f�̒�`
		grounds_[i].stageChips_.resize(grounds_[i].row_, std::vector<int>(grounds_[i].col_, 0));
	}
}

int Stage::SetStageSizeX()
{
	int num = rand() % static_cast<int>(GROUND_SIZE::MAX);
	int col;

	if (num == 0) { col = STAGE_SIZE_X_LONG; }
	else if (num == 1) { col = STAGE_SIZE_X_NORMAL; }
	else if (num == 2) { col = STAGE_SIZE_X_MIDDLE; }

	return col;
}

void Stage::LoadCsvData(int cnt)
{
	////�t�@�C���̏���
	//std::ifstream ifs = std::ifstream(groundCsv_[cnt]);
	//if (!ifs)
	//{
	//	OutputDebugString("�X�e�[�W��ifstream�������s\n");
	//	return;
	//}

	////�񎟌��z��̏ꏊ���w��p
	//int x = 0;
	//int y = 0;

	//std::string line;					//1�s�̃f�[�^���i�[����̈�
	//while (getline(ifs, line))
	//{
	//	//Split�֐��̖߂�l�󂯎��p�ϐ�
	//	std::vector<std::string> strSplit; // 1�s��1�����̓��I�z��ɕ���
	//	strSplit = AsoUtility::Split(line, ',');

	//	int chipNo;

	//	//���������f�[�^���}�b�v�z��Ɋi�[����
	//	for (int x = 0; x < strSplit.size(); x++)
	//	{
	//		chipNo = stoi(strSplit[x]);
	//		grounds_[cnt].stageChips_[ y][x] = chipNo;
	//	}
	//	y++;
	//}
}

void Stage::ClearUsedGround(int cnt)
{
	int row = grounds_[cnt].row_;
	int col = grounds_[cnt].col_;

	for (int y = 0; y < row; y++)
	{
		for (int x = 0; x < col; x++)
		{
			grounds_[cnt].stageChips_[y][x] = -1;
		}
	}
}