#pragma once
#include "SceneBase.h"
class GameOverScene : public SceneBase
{

public:

	// コンストラクタ
	GameOverScene(void);

	// デストラクタ
	~GameOverScene(void);

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

	// ゲームオーバー背景
	int gameOverImage_;

	// Bボタン
	int bBottonImage_[4][1];

	// アニメーションカウンタ
	int animCnt_;

	// 1位
	int first_;

	// 2位
	int second_;

	//BGM
	int bgm_;
	int selectSound_;

};