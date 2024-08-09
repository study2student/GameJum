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

private:

	// タイトル背景
	int titleImage_;

	// ゲームスタート
	int gameStartImage_;

	// Bボタン
	int bBottonImage_[4][1];

	// アニメーションカウンタ
	int animCnt_;

};

