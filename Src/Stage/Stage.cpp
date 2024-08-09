#include <DxLib.h>
#include <iostream>
#include <fstream>
#include "../Application.h"
#include "../Utility/AsoUtility.h"
#include "Stage.h"

Stage::Stage()
{
	col_ = 0;
	row_ = 0;
	imgBack_ = 0;
	for (int i = 0; i < DIVISION_ALL_NUM; i++)
	{
		imgStageChip_[i] = 0;
	}

	for (int y = 0; y < STAGE_SIZE_Y; y++)
	{
		for (int x = 0; x < STAGE_SIZE_X_LONG; x++)
		{
			stageChips_[y][x] = 0;
		}
	}
}

Stage::~Stage()
{
}

void Stage::Init()
{	
	Reset();
	
	Load();

	LoadCsvData();

}

void Stage::Update()
{
	for (auto& ground : grounds_)
	{
		//�X�N���[������
		ground.pos_.x -= SCROLL_SPEED;

		//�n�`�̖�������ʊO�ɏo����O�ڂ̏����ʒu�ɍ��W��߂�
		if (ground.pos_.x < -(SIZE_X + HOLE_SIZE_X_) * col_)
		{
			ground.pos_.x = ((CREATE_MAX - 1) * (SIZE_X + HOLE_SIZE_X_) * DIVISION_NUM_X);
		}
	}
}

void Stage::Draw()
{
	//�w�i�̎R�̕`��
	DrawGraph(0,0,
		imgBack_,
		true);


	//�n�ʂ̕`��
	for (auto& ground : grounds_)
	{
		for (int y = 0; y < row_; y++)
		{
			for (int x = 0; x < col_; x++)
			{
				DrawGraph(ground.pos_.x + SIZE_X * x,
					ground.pos_.y + SIZE_Y * y,
					imgStageChip_[stageChips_[y][x]],
					true);

				// �f�o�b�O�p
				if (y == 12)
				{
					int tmpX = (x * SIZE_X);
					int tmpY = (y * SIZE_Y);
					DrawBox(
						tmpX - 3, tmpY - 3,
						tmpX + 3, tmpY + 3,
						0xff0000, true
					);
				}
			}
		}
	}

	DebagDraw();

	for (auto& ground : grounds_)
	{

		//DrawBox(
		//	ground.pos_.x, ground.pos_.y,
		//	ground.pos_.x + SIZE_X * 16,
		//	ground.pos_.y + SIZE_Y * 4, 0xff0000, true);

	}

}

void Stage::Release()
{
	for (int i = 0; i < DIVISION_ALL_NUM; i++)
	{
		DeleteGraph(imgStageChip_[i]);
	}
	DeleteGraph(imgBack_);
}

void Stage::Load()
{
	//�摜�ǂݍ���
	imgBack_ = LoadGraph("Data/Image/Stage/trees.png", true);

	LoadDivGraph("Data/Image/Stage/tileset.png",
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
	csvData_ = "Data/StageCsv/LongGroundCsvData.csv";

	//��
	row_ = STAGE_SIZE_Y;

	//�s
	col_ = STAGE_SIZE_X_LONG;

	Ground ground;
	for (int i = 0; i < CREATE_MAX; i++)
	{
		//���W
		ground.pos_ = {static_cast<float>(i * (SIZE_X + HOLE_SIZE_X_) * col_),
							static_cast<float>(Application::SCREEN_SIZE_Y - (SIZE_Y * row_)) };

		//�傫��
		ground.size_ = { SIZE_X * col_,
							SIZE_Y * row_ };

		grounds_.push_back(ground);
	}
}

void Stage::DebagDraw()
{
	for (auto& ground : grounds_)
	{
		Vector2 stageCecter = { static_cast<int>(ground.pos_.x + (ground.size_.x / 2)),
									static_cast<int>(ground.pos_.y + ground.size_.y / 2) };

		DrawBox(ground.pos_.x, ground.pos_.y,
			ground.pos_.x + ground.size_.x,
			ground.pos_.y + ground.size_.y,
			0x00ff00,
			false);

		DrawCircle(stageCecter.x, stageCecter.y, 10, 0xff00ff, true);
	}

}

std::vector<Stage::Ground> Stage::GetGround()
{
	return grounds_;
}

int Stage::GetChipNo(Vector2 mapPos)
{
	return stageChips_[mapPos.y][mapPos.x];
}

void Stage::LoadCsvData()
{
	//�t�@�C���̏���
	std::ifstream ifs = std::ifstream(csvData_);
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
			stageChips_[y][x] = chipNo;
		}
		y++;
	}
}
