#pragma once
#include <vector>
#include <string>
#include "../Common/Vector2F.h"
class Stage
{
public:

#pragma region 画像関連
	//画像サイズ
	static constexpr int IMG_SIZE_X = 768;
	static constexpr int IMG_SIZE_Y = 384;

	//画像分割数
	static constexpr int DIVISION_NUM_X = 12;
	static constexpr int DIVISION_NUM_Y = 6;

	//分割後の画像サイズ
	static constexpr int SIZE_X = IMG_SIZE_X / DIVISION_NUM_X;
	static constexpr int SIZE_Y = IMG_SIZE_Y / DIVISION_NUM_Y;

	//分割総数
	static constexpr int DIVISION_ALL_NUM = DIVISION_NUM_X * DIVISION_NUM_Y;
#pragma endregion 

#pragma region ステージサイズ関連
	//地面生成数
	static constexpr int CREATE_MAX = 2;

	//幅
	static constexpr int STAGE_SIZE_X_LONG = 24;
	static constexpr int STAGE_SIZE_X_NORMAL = 16;
	static constexpr int STAGE_SIZE_X_MIDDLE = 12;

	//高さ(固定)
	static constexpr int STAGE_SIZE_Y = 4;

	//穴(末尾から次の地面描画までの幅)
	static constexpr int HOLE_SIZE_X_ = 4;
#pragma endregion 
	
#pragma region 地面用構造体
	enum class GROUND_SIZE
	{
		LONG,
		MIDDLE,
		NORMAL,
		MAX
	};

	struct Ground
	{
		//列(縦幅)
		int row_;

		//行(横幅)
		int col_;

		//ステージ配列
		std::vector<std::vector<int>> stageChips_;

		//始点
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

	//初期時の足場の確保
	void SetFirstStage();

	//足場の幅の設定
	int SetStageSizeX();

	//CSVデータの読み込み
	void LoadCsvData(int cnt);

	//初期化処理
	void ClearUsedGround(int cnt);

private:

	//画像格納
	int imgStageChip_[DIVISION_ALL_NUM];

	//チップ用配列
	int chipNum_[DIVISION_NUM_Y][DIVISION_NUM_X];	
	
	//地面
	Ground grounds_[CREATE_MAX];

	//地面CSVデータ
	std::string groundCsv_[static_cast<int>(GROUND_SIZE::MAX)];

};

