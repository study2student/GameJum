#pragma once

#include "SceneBase.h"
class TitleScene : public SceneBase
{

public:
	// コンストラクタ
	TitleScene(void);

	// デストラクタ
	~TitleScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

	// サウンド用関数-----------------------------------------
	// 読み込んだ音を再生する用
	void PlaySounds(int SoundName, int Vol);

	// 読み込み用
	bool LoadSounds(void);

	// 音を再生中かどうか判断する用
	bool CheckSounds(int SoundName);

private:

	// タイトル背景
	int titleImage_;

	// タイトルロゴ
	int titleLogoImage_;

	// ゲームスタート
	int gameStartImage_;

	// Bボタン
	int bBottonImage_[4][1];

	// アニメーションカウンタ
	int animCnt_;

#pragma region 音関連
	int bgm_;
	int selectSound_;
#pragma endregion

};

