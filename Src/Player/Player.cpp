#include <string>
#include <DxLib.h>
#include "../Application.h"
#include "../Manager/SceneManager.h"
#include "../Utility/AsoUtility.h"
#include "../Common/Vector2.h"
#include "../Manager/InputManager.h"
#include "../SceneBase/GameScene.h"
#include "../Stage/Stage.h"
#include "Player.h"


Player::Player(void)
{
}

Player::~Player(void)
{
}

void Player::Init(GameScene* scene_, TYPE type, KEY_CONFIG config, PAD_CONFIG padConfig, InputManager::JOYPAD_NO padID)
{
	gameScene_ = scene_;

	// プレイヤー種別
	type_ = type;

	// キー設定
	keyConfig_ = config;

	// パッド設定
	padConfig_ = padConfig;

	padID_ = padID;

	// 画像の読み込み
	LoadImages();

	// アニメーション状態
	animState_ = ANIM_STATE::RUN;

	// 攻撃状態
	atkState_ = ATK_STATE::NONE;

	// アニメーションカウンタ
	stepAnim_ = 0;

	// 初期座標
	pos_ = { 300.0f, 350.0f };
	if (type_ == TYPE::PLAYER_2)
	{
		pos_ = { 500.0f, 350.0f };
	}

	// プレイヤー向き
	dir_ = AsoUtility::DIR::LEFT;
	if (type_ == TYPE::PLAYER_2)
	{
		dir_ = AsoUtility::DIR::RIGHT;
	}

	// 移動速度の初期化
	moveSpeed_ = 0.0f;

	// ジャンプ力
	jumpPow_ = 0.0f;

	// ジャンプ判定
	isJump_ = true;

	// ジャンプキー入力カウンタ
	// スタート直後は1回着地しないとジャンプできない
	cntJumpInput_ = INPUT_JUMP_FRAME;

	// ジャンプキー押下判定
	isPutJumpKey_ = false;

	// 衝突判定用：中心座標（pos_からの相対座標）
	hitPos_ = { 0, 8 };

	// 衝突判定用：範囲
	hitBox_ = { 16, 46};

	// ショットの硬直時間
	stepShotDelay_ = 0.0f;

	//体力
	hp_ = MAX_HP;
}

void Player::Update(void)
{
	// モーションの初期化
	animState_ = ANIM_STATE::IDLE;

	// プレイヤーの移動操作
	ProcessMove();

	// 減速
	Decelerate(MOVE_DEC);

	// 移動操作
	Move();

	// 左右の衝突判定
	//CollisionSide();

	// プレイヤーのジャンプ操作
	ProcessJump();

	// 重力を常にかける
	AddGravity();

	// ジャンプ
	Jump();

	// 足元の衝突判定
	CollisionFoot();

	// 頭の衝突判定
	//CollisionHead();


	// 攻撃
	Attack();
}

void Player::Draw(void)
{
	DrawDebug();

	// 座標変換
	Vector2 pos = pos_.ToVector2();

	if (isJump_)
	{
		animState_ = ANIM_STATE::JUMP;
	}

	// アニメーション状態
	int animState = static_cast<int>(animState_);

	// 攻撃状態
	int atkState = static_cast<int>(atkState_);

	switch (animState_)
	{
	case ANIM_STATE::IDLE:
	{
		stepAnim_ += ANIM_SPEED;
		int animIdxIdle = AsoUtility::Round(stepAnim_) % MAX_NUM_ANIM;
		DrawPlayer(images_[animState][atkState][animIdxIdle]);
	}
	case ANIM_STATE::JUMP:
	{
		stepAnim_ += ANIM_SPEED;
		int animIdx = AsoUtility::Round(stepAnim_) % MAX_NUM_ANIM;
		DrawPlayer(images_[animState][atkState][animIdx]);
	}
	break;
	case ANIM_STATE::RUN:
	{
		stepAnim_ += ANIM_SPEED;
		int animIdx = AsoUtility::Round(stepAnim_) % MAX_NUM_ANIM;
		DrawPlayer(images_[animState][atkState][animIdx]);
	}
	break;
	case ANIM_STATE::DAMAGED:
		DrawPlayer(images_[animState][0][0]);
		break;
	}

}

void Player::Release(void)
{

	int animMax = static_cast<int>(ANIM_STATE::MAX);
	int atkMax = static_cast<int>(ATK_STATE::MAX);
	int animNumMax = MAX_NUM_ANIM;
	for (int m = 0; m < animMax; m++)
	{
		for (int k = 0; k < atkMax; k++)
		{
			for (int n = 0; n < animNumMax; n++)
			{
				DeleteGraph(images_[m][k][n]);
			}
		}
	}

	// 弾画像の解放
	DeleteGraph(imgShot_);

}

void Player::Damage(int damage)
{
	hp_ -= damage;
}

int Player::GetHp_(void)
{
	return hp_;
}

Vector2F Player::GetPos(void)
{
	return pos_;
}

bool Player::IsAlive_(void)
{
	return false;
}

void Player::LoadImages(void)
{
	std::string basePath = Application::PATH_IMAGE;

	if (type_ == TYPE::PLAYER_2)
	{
		basePath = Application::PATH_IMAGE;
	}


	int anim = 0;
	int atkNone = static_cast<int>(ATK_STATE::NONE);
	int atkShot = static_cast<int>(ATK_STATE::SHOT);

	// 待機モーション
	anim = static_cast<int>(ANIM_STATE::IDLE);

	//images_[anim][atkNone][0] = LoadGraph((basePath + "Player/Idle.png").c_str());
	LoadDivGraph(
		(basePath + "Player/Idle.png").c_str(),
		MAX_NUM_ANIM,
		MAX_NUM_ANIM, 1,
		SIZE_X, SIZE_Y,
		&images_[anim][atkNone][0],
		false);

	images_[anim][atkShot][0] = LoadGraph((basePath + "Player/IdleShot.png").c_str());

	// ジャンプ
	anim = static_cast<int>(ANIM_STATE::JUMP);
	//images_[anim][atkNone][0] = LoadGraph((basePath + "Player/Jump.png").c_str());
	LoadDivGraph(
		(basePath + "Player/Jump.png").c_str(),
		MAX_NUM_ANIM,
		MAX_NUM_ANIM, 1,
		SIZE_X, SIZE_Y,
		&images_[anim][atkNone][0],
		false);

	// 被ダメージ
	anim = static_cast<int>(ANIM_STATE::DAMAGED);
	images_[anim][atkNone][0] = LoadGraph((basePath + "Player/Damaged.png").c_str());

	// 走る
	anim = static_cast<int>(ANIM_STATE::RUN);

	//P1
	LoadDivGraph(
		(basePath + "Player/Run.png").c_str(),
		MAX_NUM_ANIM,
		MAX_NUM_ANIM, 1,
		SIZE_X, SIZE_Y,
		&images_[anim][atkNone][0],
		false);

	// 弾画像
	imgShot_ = LoadGraph((basePath + "Shot.png").c_str());

	// 体力画像
	imgHp_ = LoadGraph((basePath + "Player/Heart.png").c_str());
}

void Player::DrawPlayer(int handleId)
{

	// 座標変換
	Vector2 pos = pos_.ToVector2();

	// プレイヤーの向き
	bool isLeftDir = true;
	if (dir_ == AsoUtility::DIR::RIGHT)
	{
		isLeftDir = false;
	}

	// 描画(座標、拡大率、回転、ハンドルID、透過フラグ、横反転、縦反転)
	DrawRotaGraph(
		pos.x, pos.y,
		1.0, 0.0, handleId, true,
		isLeftDir);

}

void Player::DrawDebug(void)
{
	DrawFormatString(0, 0, 0x000000, "プレイヤー座標(%.2f, %.f)", pos_.x, pos_.y);

	DrawFormatString(0, 20, 0x000000, "移動速度(%.2f)", moveSpeed_);

	DrawFormatString(0, 40, 0x000000, "ジャンプ力(%.2f)", jumpPow_);

	Vector2 pos = pos.ToVector2F();

	DrawBox(pos_.x - SIZE_X / 2, pos_.y - SIZE_Y / 2, pos_.x + SIZE_X / 2, pos_.y + SIZE_Y / 2, 0xffffff, false);

	//DrawBox(pos_.x - SIZE_X / 2, pos_.y - SIZE_Y / 2, pos_.x + SIZE_X / 2, pos_.y + SIZE_Y / 2, 0xffffff, false);

	DrawBox(pos.x - 3, pos.y - 3, pos.x + 3, pos.y + 3, 0xff0000, true);

	// オレンジ
	int color = 0xff8c00;

	// 左の座標
	Vector2 headPosL = GetColPos(COL_LR::L, COL_TD::T);
	// 左の座標
	Vector2 corePosL = GetColPos(COL_LR::L, COL_TD::C);
	// 足元座標（左）
	Vector2 footPosL = GetColPos(COL_LR::L, COL_TD::D);

	pos = headPosL;
	DrawBox(pos.x - 3, pos.y - 3, pos.x + 3, pos.y + 3, 0xff0000, true);
	pos = corePosL;
	DrawBox(pos.x - 3, pos.y - 3, pos.x + 3, pos.y + 3, 0xff0000, true);
	pos = footPosL;
	DrawBox(pos.x - 3, pos.y - 3, pos.x + 3, pos.y + 3, 0xff0000, true);

	// 右の座標
	Vector2 headPosR = GetColPos(COL_LR::R, COL_TD::T);
	// 右の座標
	Vector2 corePosR = GetColPos(COL_LR::R, COL_TD::C);
	// 足元座標（右）
	Vector2 footPosR = GetColPos(COL_LR::R, COL_TD::D);

	pos = headPosR;
	DrawBox(pos.x - 3, pos.y - 3, pos.x + 3, pos.y + 3, 0xff0000, true);
	pos = corePosR;
	DrawBox(pos.x - 3, pos.y - 3, pos.x + 3, pos.y + 3, 0xff0000, true);
	pos = footPosR;
	DrawBox(pos.x - 3, pos.y - 3, pos.x + 3, pos.y + 3, 0xff0000, true);

	// 足元座標
	Vector2 footPosC = GetColPos(COL_LR::C, COL_TD::D);

	pos = footPosC;
	DrawBox(pos.x - 3, pos.y - 3, pos.x + 3, pos.y + 3, 0xff0000, true);

	// 頭の座標座標
	Vector2 headPosC = GetColPos(COL_LR::C, COL_TD::T);

	pos = headPosC;
	DrawBox(pos.x - 3, pos.y - 3, pos.x + 3, pos.y + 3, 0xff0000, true);

	// デバッグ用：足元衝突判定
	Vector2 footPos = pos;
	footPos.y += (4 + 24);

	// 足元：中央
	DrawBox(footPos.x - 3, footPos.y - 3, footPos.x + 3, footPos.y + 3, color, true);


	DrawBox(footPos.x - 3 - 16, footPos.y - 3, footPos.x + 3 - 16, footPos.y + 3, color, true);

	// デバッグ用：頭の衝突判定
	Vector2 headPos = pos;
	headPos.y += (8 - 24);

	// 頭：中央
	DrawBox(headPos.x - 3, headPos.y - 3, headPos.x + 3, headPos.y + 3, color, true);
	DrawBox(headPos.x - 3, headPos.y - 3, headPos.x + 3, headPos.y + 3, color, true);
	DrawBox(headPos.x - 3, headPos.y - 3, headPos.x + 3, headPos.y + 3, color, true);
}

void Player::DrawHP(int playerNum)
{
	int scX = Application::SCREEN_SIZE_X;
	int scY = Application::SCREEN_SIZE_Y;
	for (int i = 0; i <  80 * hp_; i += 80)
	{
		DrawRotaGraphFastF(0 + 35 + i, 35 + 70 * playerNum, 0.1f, 0.0f, imgHp_, true);
	}

}

void Player::ProcessMove(void)
{
	auto& ins = InputManager::GetInstance();

	// 左方向
	if (ins.IsNew(keyConfig_.LEFT))
	{
		animState_ = ANIM_STATE::RUN;

		dir_ = AsoUtility::DIR::LEFT;
		// 加速
		Accele(-MOVE_ACC);
	}

	if (ins.InputManager::GetJPadInputState(padID_).AKeyLX) {
		animState_ = ANIM_STATE::RUN;
		dir_ = AsoUtility::DIR::LEFT;
		Accele(-MOVE_ACC);
	}


	// 右方向
	if (ins.IsNew(keyConfig_.RIGHT))
	{
		animState_ = ANIM_STATE::RUN;

		dir_ = AsoUtility::DIR::RIGHT;
		// 加速
		Accele(MOVE_ACC);
	}

	if (ins.InputManager::GetJPadInputState(padID_).AKeyRX)
	{
		animState_ = ANIM_STATE::RUN;

		dir_ = AsoUtility::DIR::RIGHT;
		// 加速
		Accele(MOVE_ACC);
	}
}

void Player::Move(void)
{
	pos_.x += moveSpeed_;
}

void Player::Accele(float speed)
{  
	moveSpeed_ += speed;

	// 速度制限(右方向)
	if (moveSpeed_ > MAX_MOVE_SPEED)
	{
		moveSpeed_ = MAX_MOVE_SPEED;
	}

	// 速度制限(左方向)
	if (moveSpeed_ < -MAX_MOVE_SPEED)
	{
		moveSpeed_ = -MAX_MOVE_SPEED;
	}

}

void Player::Decelerate(float speed)
{

	// 右方向の移動を減速させる
	if (moveSpeed_ > 0.0f)
	{
		moveSpeed_ -= speed;
		if (moveSpeed_ < 0.0f)
		{
			moveSpeed_ = 0.0f;
		}
	}

	// 左方向の移動を減速させる
	if (moveSpeed_ < 0.0f)
	{
		moveSpeed_ += speed;
		if (moveSpeed_ > 0.0f)
		{
			moveSpeed_ = 0.0f;
		}
	}
}

void Player::ProcessJump(void)
{

	// 単純ジャンプ
	//if (InputManager::GetInstance().IsNew(KEY_INPUT_M) && !isJump_)
	//{
	//	SetJumpPow(-MAX_JUMP_POW);
	//	isJump_ = true;
	//}
	auto& ins = InputManager::GetInstance();

	// 接地してないと、ジャンプを開始できないようにする
	if ((ins.IsTrgDown(keyConfig_.JUMP) 
		|| ins.IsPadBtnTrgDown(padID_, InputManager::JOYPAD_BTN::RIGHT))
		&& !isJump_)
	{
		isJump_ = true;
		isPutJumpKey_ = true;
	}
	if (static_cast<bool>(GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_A) && !isJump_)
	{
		isJump_ = true;
		isPutJumpKey_ = true;
	}
	// 入力時間に応じてジャンプ量を変更する
	if (ins.IsNew(keyConfig_.JUMP) 
		&& ins.IsPadBtnNew(padID_, InputManager::JOYPAD_BTN::RIGHT)
		&& cntJumpInput_ < INPUT_JUMP_FRAME
		&& isPutJumpKey_)
	{
		// ジャンプカウンタを増やす
		cntJumpInput_++;

		//意味がない
		//SetJumpPow(-MAX_JUMP_POW);

		// 加算はできたがジャンプ力が大きすぎる
		//float pow = jumpPow_ - MAX_JUMP_POW;
		//SetJumpPow(pow);

		// 
		float pow = jumpPow_ - (MAX_JUMP_POW / static_cast<float>(INPUT_JUMP_FRAME));
		SetJumpPow(pow);

	}

	// 2段ジャンプを禁止する
	if (ins.IsTrgUp(keyConfig_.JUMP))
	{
		// ジャンプボタンを離された時
		cntJumpInput_ = INPUT_JUMP_FRAME;
	}

}

void Player::Jump(void)
{
	pos_.y += jumpPow_;

	//// 仮の接地（衝突）判定
	//if (pos_.y > 380.0f)
	//{
	//	pos_.y = 380.0f;

	//	// 地面についたのでジャンプをリセット
	//	isJump_ = false;
	//	SetJumpPow(0.0f);

	//	// 設置したら
	//	cntJumpInput_ = 0;
	//}
}

void Player::SetJumpPow(float pow)
{
	// ジャンプ力を設定
	jumpPow_ = pow;

	// 重力がかかり過ぎるのを防ぐ
	if (jumpPow_ > MAX_JUMP_POW)
	{
		jumpPow_ = MAX_JUMP_POW;
	}

}

void Player::CollisionFoot(void)
{


	// 足元座標
	Vector2 s = GetColPos(COL_LR::L, COL_TD::T);
	Vector2 e = GetColPos(COL_LR::R, COL_TD::D);

	if (gameScene_->IsCollisionStage(s, e))
	{
		pos_.y = 363;
		//地面についたらジャンプをリセットする
		isJump_ = false;
		SetJumpPow(0.0f);
		// 接地したらジャンプカウンタを元に戻す
		cntJumpInput_ = 0;

		// ジャンプキーの押下判定
		isPutJumpKey_ = false;
	}




	// 接地判定（足元の衝突判定）

	// 足元座標
	Vector2 footPosC = GetColPos(COL_LR::C, COL_TD::D);


	// 足元座標（左）
	Vector2 footPosL = GetColPos(COL_LR::L, COL_TD::D);

	// 足元座標（右）
	Vector2 footPosR = GetColPos(COL_LR::R, COL_TD::D);




	//if (gameScene_->IsCollisionStage(footPosC)
	//	|| gameScene_->IsCollisionStage(footPosL)
	//	|| gameScene_->IsCollisionStage(footPosR)
	//	)
	//{
	//	Vector2 mapPos = gameScene_->World2MapPos(footPosC);
	//	pos_.y = static_cast<float>(mapPos.y * Stage::SIZE_Y - 1 - hitBox_.y - hitPos_.y);
	//	// 地面についたのでジャンプをリセットする
	//	isJump_ = false;
	//	SetJumpPow(0.0f);
	//	// 接地したらジャンプカウンタを元に戻す
	//	cntJumpInput_ = 0;

	//	// ジャンプキーの押下判定
	//	isPutJumpKey_ = false;
	//}

	//// 空中判定
	//footPosC.y += 1;
	//footPosL.y += 1;
	//footPosR.y += 1;
	//if (!(gameScene_->IsCollisionStage(footPosC)
	//	|| gameScene_->IsCollisionStage(footPosL)
	//	|| gameScene_->IsCollisionStage(footPosR))
	//	)
	//{
	//	// 接地していないので、ジャンプ判定にする
	//	isJump_ = true;
	//}
}

void Player::CollisionHead(void)
{
	// 頭の衝突判定（足元の衝突判定）

	// 頭の座標座標
	Vector2 headPosC = GetColPos(COL_LR::C, COL_TD::T);


	// 頭の座標（左）
	Vector2 headPosL = GetColPos(COL_LR::L, COL_TD::T);


	// 頭の座標（右）
	Vector2 headPosR = GetColPos(COL_LR::R, COL_TD::T);


	//if (gameScene_->IsCollisionStage(headPosC)
	//	|| gameScene_->IsCollisionStage(headPosL)
	//	|| gameScene_->IsCollisionStage(headPosR)
	//	)
	//{
	//	Vector2 mapPos = gameScene_->World2MapPos(headPosC);
	//	pos_.y = static_cast<float>(mapPos.y * Stage::SIZE_Y + Stage::SIZE_Y + SIZE_Y / 2 + hitPos_.y - hitBox_.y);

	//	SetJumpPow(0.0f);
	//}

}

void Player::CollisionSide(void)
{
	//// 左右の衝突判定（左右の衝突判定）

	//// 左の座標
	//Vector2 headPosL = GetColPos(COL_LR::L, COL_TD::T);
	//// 左の座標
	//Vector2 corePosL = GetColPos(COL_LR::L, COL_TD::C);
	//// 足元座標（左）
	//Vector2 footPosL = GetColPos(COL_LR::L, COL_TD::D);

	//if (gameScene_->IsCollisionStage(headPosL)
	//	|| gameScene_->IsCollisionStage(footPosL)
	//	|| gameScene_->IsCollisionStage(corePosL)
	//	)
	//{
	//	Vector2 mapPos = gameScene_->World2MapPos(headPosL);
	//	pos_.x = static_cast<float>(mapPos.x * Stage::SIZE_X
	//		+ Stage::SIZE_X + hitBox_.x);

	//}

	//if (pos_.x > pos_.x + SIZE_X)
	//{
	//	Vector2 mapPos = gameScene_->World2MapPos(headPosL);
	//	pos_.x = static_cast<float>(mapPos.x * Stage::SIZE_X
	//		+ Stage::SIZE_X + hitBox_.x);

	//}


	//// 右の座標
	//Vector2 headPosR = GetColPos(COL_LR::R, COL_TD::T);
	//// 右の座標
	//Vector2 corePosR = GetColPos(COL_LR::R, COL_TD::C);
	//// 足元座標（右）
	//Vector2 footPosR = GetColPos(COL_LR::R, COL_TD::D);

	//if (gameScene_->IsCollisionStage(headPosR)
	//	|| gameScene_->IsCollisionStage(footPosR)
	//	|| gameScene_->IsCollisionStage(corePosR)
	//	)
	//{
	//	Vector2 mapPos = gameScene_->World2MapPos(headPosR);
	//	pos_.x = static_cast<float>(mapPos.x * Stage::SIZE_X
	//		- 1 - hitBox_.x);

	//}

	//InputManager& ins = InputManager::GetInstance();
	//if (ins.IsTrgDown(KEY_INPUT_Z))
	//{
	//	hp_--;
	//}
}

Vector2 Player::GetColPos(COL_LR lr, COL_TD td)
{
	Vector2 ret = pos_.ToVector2();

	// 相対座標を足す
	ret.x += hitPos_.x;
	ret.y += hitPos_.y;

	// 左右
	switch (lr)
	{
	case Player::COL_LR::L:
		ret.x -= hitBox_.x;
		break;
	case Player::COL_LR::R:
		ret.x += hitBox_.x;
		break;
	}

	// 上下
	switch (td)
	{
	case Player::COL_TD::T:
		ret.y -= hitBox_.y;
		break;
	case Player::COL_TD::D:
		ret.y += hitBox_.y;
		break;
	}

	return ret;
}

void Player::Attack(void)
{
	// ボタンが押されたら弾を生成

	// 攻撃キーを押すと、弾を生成
	if (InputManager::GetInstance().IsNew(keyConfig_.ATTAK)
		&& stepShotDelay_ <= 0.0f)
	{
		// 有効な球を取得する
		//Shot* shot = GetValidShot();

		// ロックマンの腕の長さ分座標をずらす
		Vector2F pos = pos_;

		//if (dir_ == AsoUtility::DIR::RIGHT)
		//{
		//	pos.x += 20.0f;
		//}
		//
		//// 
		//if (dir_ == AsoUtility::DIR::LEFT)
		//{
		//	pos.x -= 20.0f;
		//}

		// 弾を生成(弾発射の準備)
		Vector2F dir = AsoUtility::Normalize(dir_);
		//shot->CreateShot(pos.ToVector2(), dir);

		float powX = 20.0f;
		float movePowX = dir.x * powX;
		pos.x += movePowX;

		if (isJump_)
		{
			pos.y -= 10.0f;
		}
		else
		{
			pos.y += 5.0f;
		}

		// 弾の発射後の硬直時間セット
		stepShotDelay_ = SHOT_DELAY;
	}


	atkState_ = ATK_STATE::NONE;
	if (stepShotDelay_ > 0.0f)
	{
		// 弾発射後の硬直時間を減らす
		//stepShotDelay_ -= 1.0f / SceneManager::DEFAULT_FPS;

		// 弾を撃っている間は、攻撃中とする
		atkState_ = ATK_STATE::SHOT;
	}
}

//Shot* Player::GetValidShot(void)
//{
//	auto size = shots_.size();
//	for (int i = 0; i < size; i++)
//	{
//		if (!shots_[i]->IsAlive())
//		{
//			// 生存していない弾なので
//			// このインスタンスをリサイクル
//			return shots_[i];
//		}
//	}
//
//	// 生存していない弾が見つからなかった
//	Shot* shot = new Shot(imgShot_);
//	shots_.push_back(shot);
//
//	return shot;
//}

void Player::AddGravity(void)
{
	// 現在のジャンプ力に重力を加える
	float pow = jumpPow_ + GRAVITY;
	SetJumpPow(pow);
}
