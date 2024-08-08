#pragma once
#include "../Common/Vector2.h"
#include "../Utility/AsoUtility.h"

class GameScene;

class Player
{
public:
	// 方向ごとのアニメーション数
	static constexpr int MAX_NUM_ANIM = 15;

	static constexpr int SIZE_X = 153;
	static constexpr int SIZE_Y = 142;

	// 移動速度
	static constexpr int SPEED_DEFAULT = 5;

	// アニメーションスピード
	static constexpr float ANIM_SPEED = 0.1f;

	// 移動速度の最大値
	static constexpr float MAX_MOVE_SPEED = 3.5f;

	// 加速(accelerator=アクセレレーター)
	static constexpr float MOVE_ACC = 0.25f;

	// 減速(decelarate=ディセラレイト)
	static constexpr float MOVE_DEC = 0.05f;

	// 最大ジャンプ力
	static constexpr float MAX_JUMP_POW = 8.5f;

	// 最大体力
	static constexpr int MAX_HP = 3;

	// 重力
	static constexpr float GRAVITY = 0.25f;

	//	ジャンプキー入力を受け付けるフレーム数
	static constexpr int INPUT_JUMP_FRAME = 6;

	//	弾発射後の硬直時間
	static constexpr float SHOT_DELAY = 1.0f;

	// アニメーション状態
	enum  class ANIM_STATE
	{
		IDLE,
		RUN,
		JUMP,
		DAMAGED,
		MAX
	};

	// 攻撃状態
	enum  class ATK_STATE
	{
		NONE,
		SHOT,
		MAX
	};

	// 衝突座標（左右）
	enum class COL_LR
	{
		C, // 中央
		L, // 左
		R  // 右
	};

	// 衝突座標（上下）
	enum class COL_TD
	{
		C, // 中央
		T, // 上
		D  // 下
	};

	// プレイヤー種類
	enum class TYPE
	{
		PLAYER_1,
		PLAYER_2
	};

	// キーコンフィグ
	struct  KEY_CONFIG
	{
		int UP;
		int DOWN;
		int LEFT;
		int RIGHT;
		int ATTAK;
		int JUMP;
	};

	enum class JoypadButton {
		UP = PAD_INPUT_UP,
		DOWN = PAD_INPUT_DOWN,
		LEFT = PAD_INPUT_LEFT,
		RIGHT = PAD_INPUT_RIGHT,
		ACTION = PAD_INPUT_6
	};

	// プレイヤーごとの入力マッピング
	struct PlayerInput {
		int padId;
		JoypadButton up;
		JoypadButton down;
		JoypadButton left;
		JoypadButton right;
		JoypadButton action;
	};

	// コンストラクタ
	Player(void);

	// デストラクタ
	~Player(void);

	void Init(GameScene* scene_, TYPE type, KEY_CONFIG config);
	void Update(void);
	void Draw(void);
	void Release(void);

	// ダメージを与える処理
	void Damage(int damage);

	// 体力描画
	void DrawHP(int playerNum);

	// HPの取得（ゲッター）
	int GetHp_(void);

	// 座標の取得(ゲッター)
	Vector2F GetPos(void);

	// 生存判定（ゲッター）
	bool IsAlive_(void);

private:


	// ゲームシーンのポインタ変数
	GameScene* gameScene_;

	// 画像［向き］［アニメーション］
	int images_[static_cast<int>(ANIM_STATE::MAX)]
		[static_cast<int>(ATK_STATE::MAX)][MAX_NUM_ANIM];

	// 座標
	Vector2F pos_;

	// アニメーション状態
	ANIM_STATE animState_;

	// 攻撃状態
	ATK_STATE atkState_;

	// アニメーションカウンタ
	float stepAnim_;

	// プレイヤーの向き
	AsoUtility::DIR dir_;

	// 移動速度
	float moveSpeed_;

	// ジャンプ力
	float jumpPow_;

	// ジャンプ中判定
	bool isJump_;

	// ジャンプ
	bool isPutJumpKey_;

	// ジャンプキー入力カウンタ
	int cntJumpInput_;

	// 体力
	int hp_;

	// 体力画像
	int imgHp_;

	// 衝突判定用：中心座標（pos_からの相対座標）
	Vector2 hitPos_;

	// 衝突判定用：範囲
	Vector2 hitBox_;

	// プレイヤー種別(1P or 2P)
	TYPE type_;

	// キー設定
	KEY_CONFIG keyConfig_;

	// 弾画像
	int imgShot_;

	// 弾発射後の硬直時間
	float stepShotDelay_;

	// 画像の読み込み
	void LoadImages(void);

	// プレイヤーの描画
	void DrawPlayer(int handleId);

	// デバッグ用の描画
	void DrawDebug(void);

	// プレイヤーの移動操作
	void ProcessMove(void);

	// 移動操作
	void Move(void);

	// 加速
	void Accele(float speed);

	// 減速（スピードを減少させる）
	void Decelerate(float speed);

	// 重力をかける
	void AddGravity(void);

	// プレイヤーのジャンプ操作
	void ProcessJump(void);

	// ジャンプ
	void Jump(void);

	// ジャンプ力の設定
	void SetJumpPow(float pow);

	// 足元の衝突判定
	void CollisionFoot(void);

	// 頭の衝突判定
	void CollisionHead(void);

	// 左右の衝突判定
	void CollisionSide(void);

	// 衝突座標を取得する
	Vector2 GetColPos(COL_LR lr, COL_TD td);

	// 攻撃処理
	void Attack(void);


};

