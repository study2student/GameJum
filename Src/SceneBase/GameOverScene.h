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

};