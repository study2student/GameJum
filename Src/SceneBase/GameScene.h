#pragma once
#include "SceneBase.h"
class Enemy;
class Vector2;
class Player;
class BulletGimmick;
class Stage;

class GameScene : public SceneBase
{
public:
	static constexpr int BG_SIZE = 1047;

	static constexpr int GAME_PLAYER_NUM = 2;

	// コンストラクタ
	GameScene(void);

	// デストラクタ
	~GameScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

private:

	// 弾のギミック
	BulletGimmick* bulletGimmick_;

	// Enemy用ポインタ
	Enemy* enemy_;

	// プレイヤークラスのポインタ
	Player* player_[GAME_PLAYER_NUM];

	// 生存時間
	float aliveTimeP1_;
	float aliveTimeP2_;

	// 衝突判定
	void GimmickCollision(void);

	// ステージとの衝突判定
	void StageCollision(void);

	// 敵本体の当たり判定
	void EnemyCollision(void);
	// 近づいたら弾を発射する用の当たり判定
	void ShotCollision(void);
	// 弾の当たり判定
	void BulletCollision(void);

	// 衝突判定
	bool IsCollisionRect(Vector2 stPos1, Vector2 edPos1, Vector2 stPos2, Vector2 edPos2);

	// 衝突判定
	bool IsCollisionRectCenter(Vector2 centerPos1, Vector2 size1, Vector2 centerPos2, Vector2 size2);

	// サウンド用関数-----------------------------------------
	// 読み込んだ音を再生する用
	void PlaySounds(int SoundName, int Vol);

	// 読み込み用
	bool LoadSounds(void);			

	// 音を再生中かどうか判断する用
	bool CheckSounds(int SoundName);

	//サウンド用変数-------------------------------------------
	int bgm_;
	int enemyShotSound_;

	//ステージ
	Stage* stage_;

	// 背景関連
	int bgImage;			// グラフィックハンドル
	int bgPosX1;			// 1枚目の背景
	int bgPosX2;			// 2枚目の背景
	int bgSizeX;			// 背景の縦サイズ
};

