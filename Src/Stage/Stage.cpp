#include <DxLib.h>
#include <iostream>
#include <fstream>
#include "../Application.h"
#include "../Utility/AsoUtility.h"
#include "Stage.h"

Stage::Stage()
{
	for (int i = 0; i < DIVISION_ALL_NUM; i++)
	{
		imgStageChip_[i] = 0;
	}
}

Stage::~Stage()
{
}

void Stage::Init()
{	
	Reset();
	
	Load();

	for (int i = 0; i < CREATE_MAX; i++)
	{
		LoadCsvData(i);
	}
}

void Stage::Update()
{
	//if()
}

void Stage::Draw()
{
	for (int i = 0; i < CREATE_MAX; i++)
	{
		for (int y = 0; y < grounds_[i].row_; y++)
		{
			for (int x = 0; x < grounds_[i].col_; x++)
			{
				DrawGraph(grounds_[i].pos_.x + SIZE_X * x,
					grounds_[i].pos_.y + SIZE_Y * y,
					imgStageChip_[grounds_[i].stageChips_[y][x]],
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
	int ret;

	//�摜�ǂݍ���
	ret = LoadDivGraph("Data/Stage/tileset.png",
		DIVISION_ALL_NUM,
		DIVISION_NUM_X,
		DIVISION_NUM_Y,
		SIZE_X,
		SIZE_Y,
		&(imgStageChip_[0]));

	if (ret == -1)
	{
		return;
	}
}

void Stage::Reset()
{
	//CSV�f�[�^
	groundCsv_[static_cast<int>(GROUND_SIZE::MIDDLE)] = "Data/StageCsv/MiddleGroundCsvData.csv";
	groundCsv_[static_cast<int>(GROUND_SIZE::NORMAL)] = "Data/StageCsv/NormalGroundCsvData.csv";
	groundCsv_[static_cast<int>(GROUND_SIZE::LONG)] = "Data/StageCsv/LongGroundCsvData.csv";

	for (int i = 0; i < CREATE_MAX; i++)
	{
		//�n�ʃT�C�Y�̎��
		grounds_[i].type_ = RandGroundType();

		//��
		grounds_[i].row_ = STAGE_SIZE_Y;

		//�s
		grounds_[i].col_ = SetCol(grounds_[i].type_);

		//���W
		grounds_[i].pos_ = { static_cast<float>(i * (SIZE_X + HOLE_SIZE_X_) * DIVISION_NUM_X),
							static_cast<float>(Application::SCREEN_SIZE_Y - (SIZE_Y * grounds_[i].row_)) };

		//�X�e�[�W�`�b�v�̐ݒ�
		//�v�f�̒�`
		grounds_[i].stageChips_.resize(grounds_[i].row_, std::vector<int>(grounds_[i].col_, 0));
	}
}

Stage::GROUND_SIZE Stage::RandGroundType()
{
	int num = rand() % static_cast<int>(GROUND_SIZE::MAX);
	GROUND_SIZE type;

	if (num == 0) { type = GROUND_SIZE::LONG; }
	else if (num == 1) { type = GROUND_SIZE::MIDDLE; }
	else if (num == 2) { type = GROUND_SIZE::NORMAL; }

	return type;
}

int Stage::SetCol(GROUND_SIZE type)
{
	int col;

	switch (type)
	{
	case GROUND_SIZE::LONG:
		col = STAGE_SIZE_X_LONG;
		break;

	case GROUND_SIZE::MIDDLE:
		col = STAGE_SIZE_X_MIDDLE;
		break;

	case GROUND_SIZE::NORMAL:
		col = STAGE_SIZE_X_NORMAL;
		break;

	default:
		break;
	}

	return col;
}

void Stage::LoadCsvData(int cnt)
{
	//�t�@�C���̏���
	std::ifstream ifs = std::ifstream(groundCsv_[static_cast<int>(grounds_->type_)]);
	if (!ifs)
	{
		OutputDebugString("�X�e�[�W��ifstream�������s\n");
		return;
	}

	//�񎟌��z��̏ꏊ���w��p
	int x = 0;
	int y = 0;

	std::string line;					//1�s�̃f�[�^���i�[����̈�
	while (getline(ifs, line))
	{
		//Split�֐��̖߂�l�󂯎��p�ϐ�
		std::vector<std::string> strSplit; // 1�s��1�����̓��I�z��ɕ���
		strSplit = AsoUtility::Split(line, ',');

		int chipNo;

		//���������f�[�^���}�b�v�z��Ɋi�[����
		for (int x = 0; x < strSplit.size(); x++)
		{
			chipNo = stoi(strSplit[x]);
			grounds_[cnt].stageChips_[y][x] = chipNo;
		}
		y++;
	}
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