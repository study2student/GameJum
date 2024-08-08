#pragma once
#include "../Common/Vector2.h"

class Player
{
public:
	// 攻撃状態
	enum  class ATK_STATE
	{
		NONE,
		SHOT,
		MAX
	};

	// コンストラクタ
	Player(void);

	// デストラクタ
	~Player(void);

	void Init();
	void Update(void);
	void Draw(void);
	void Release(void);

private:
	//プレイヤー画像
	int images;
};