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

	LoadCsvData();

}

void Stage::Update()
{
	//if()
}

void Stage::Draw()
{
	for (int i = 0; i < CREATE_MAX; i++)
	{
		for (int y = 0; y < row_; y++)
		{
			for (int x = 0; x < col_; x++)
			{
				DrawGraph(grounds_[i].pos_.x + SIZE_X * x,
					grounds_[i].pos_.y + SIZE_Y * y,
					imgStageChip_[stageChips_[y][x]],
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

	//画像読み込み
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
	//CSVデータ
	csvData_ = "Data/StageCsv/LongGroundCsvData.csv";

	//列
	row_ = STAGE_SIZE_Y;

	//行
	col_ = STAGE_SIZE_X_LONG;

	Ground ground;
	for (int i = 0; i < 2; i++)
	{
		//座標
		ground.pos_ = {static_cast<float>(i * (SIZE_X + HOLE_SIZE_X_) * DIVISION_NUM_X),
							static_cast<float>(Application::SCREEN_SIZE_Y - (SIZE_Y * row_)) };
		grounds_.push_back(ground);
	}
}

//Stage::GROUND_SIZE Stage::RandGroundType()
//{
//	int num = rand() % static_cast<int>(GROUND_SIZE::MAX);
//	GROUND_SIZE type;
//
//	if (num == 0) { type = GROUND_SIZE::LONG; }
//	else if (num == 1) { type = GROUND_SIZE::MIDDLE; }
//	else if (num == 2) { type = GROUND_SIZE::NORMAL; }
//
//	return type;
//}

void Stage::ClearUsedGround(int cnt)
{
	for (int y = 0; y < row_; y++)
	{
		for (int x = 0; x < col_; x++)
		{
			stageChips_[y][x] = -1;
		}
	}
}

std::vector<Stage::Ground> Stage::GetGround()
{
	return grounds_;
}

void Stage::LoadCsvData()
{
	//ファイルの準備
	std::ifstream ifs = std::ifstream(csvData_);
	if (!ifs)
	{
		OutputDebugString("ステージのifstream準備失敗\n");
		return;
	}

	//二次元配列の場所を指定用
	int x = 0;
	int y = 0;

	std::string line;					//1行のデータを格納する領域
	while (getline(ifs, line))
	{
		//Split関数の戻り値受け取り用変数
		std::vector<std::string> strSplit; // 1行を1文字の動的配列に分割
		strSplit = AsoUtility::Split(line, ',');

		int chipNo;

		//分割したデータをマップ配列に格納する
		for (int x = 0; x < strSplit.size(); x++)
		{
			chipNo = stoi(strSplit[x]);
			stageChips_[y][x] = chipNo;
		}
		y++;
	}
}
