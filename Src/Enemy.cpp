#include <DxLib.h>
#include <cmath> 
#include "Application.h"
#include "Enemy.h"

Enemy::Enemy(void)
{
}

Enemy::~Enemy(void)
{
}

void Enemy::Init(void)
{
	std::string basePath = Application::PATH_IMAGE;

	// 弾画像の読み込み
	imgBullet_ = LoadGraph((basePath + "Enemy/bullet.png").c_str());
	if (imgBullet_ == -1)
	{
		OutputDebugString("bullet画像の初期化失敗");
		return;
	}

	// 画像の読み込み
	int ret;
	ret = LoadDivGraph(
		(basePath + "Enemy/blue_test.png").c_str(),
		ANIM_MAX_NUM_X * ANIM_MAX_NUM_Y,
		ANIM_MAX_NUM_X,
		ANIM_MAX_NUM_Y,
		SIZE_X,
		SIZE_Y,
		&(imgsDino_[0][0])
	);

	if (ret == -1)
	{
		OutputDebugString("blue_testの読み込み失敗");
		return;
	}

	// アニメーション用
	cntAnim_ = 0;
	speedAnim_ = 0.1f;
	animNum_ = 0;

	// 敵の座標
	pos_ = { Application::SCREEN_SIZE_X /2,Application::SCREEN_SIZE_Y /2};
	// 敵の状態
	state_ = ANIM_STATE::IDLE;
	atkState_ = ATK_STATE::NONE;
	dir_ = DIR::RIGHT;

	// 敵の移動量
	movePow_ = 0.5f;

	speed = 2.0f;
	bulletRadius = 5.0f;

	// 衝突判定用：中心座標（pos_からの相対座標）
	hitPos_ = { 0, 8 };

	// 衝突判定用：範囲
	hitBox_ = { 16, 24 };
}

void Enemy::Update(void)
{
	cntAnim_++;

	Debug();

	Move();

	switch (state_)
	{
	case ANIM_STATE::IDLE:
		animNum_ = static_cast<int>(
			static_cast<float>(cntAnim_) * speedAnim_)
			% IDLE_ANIM_NUM;

		break;

	case ANIM_STATE::WALK:
		animNum_ = static_cast<int>(
			static_cast<float>(cntAnim_) * speedAnim_)
			% WALK_ANIM_NUM;

		break;	
	
	case ANIM_STATE::KICK:
		animNum_ = static_cast<int>(
			static_cast<float>(cntAnim_) * speedAnim_)
			% KICK_ANIM_NUM;
		if (animNum_ == 3) {
			state_ = ANIM_STATE::IDLE;
			break;
		}

	case ANIM_STATE::HIT:
		animNum_ = static_cast<int>(
			static_cast<float>(cntAnim_) * speedAnim_)
			% HIT_ANIM_NUM;
		break;

	case ANIM_STATE::RUN:
		animNum_ = static_cast<int>(
			static_cast<float>(cntAnim_) * speedAnim_)
			% RUN_ANIM_NUM;

		break;

	default:
		break;
	}

	//攻撃
	atkState_ = ATK_STATE::NONE;		//基本は攻撃していない
	if (CheckHitKey(KEY_INPUT_N))
	{
		atkState_ = ATK_STATE::SHOT;
		Shot();
	}
}

void Enemy::Draw(void)
{
	EnemyDraw();

	if (atkState_ == ATK_STATE::SHOT)
	{
		BulletDraw();
	}
	
}

void Enemy::Release(void)
{
	for (int y = 0; y < ANIM_MAX_NUM_Y; y++)
	{
		for (int x = 0; x < ANIM_MAX_NUM_X; x++)
		{
			DeleteGraph(imgsDino_[y][x]);
		}
	}
}

void Enemy::EnemyDraw(void)
{
	if (dir_ == DIR::RIGHT)
	{
		// 中心座標で描画
		DrawRotaGraph(
			pos_.x,
			pos_.y,
			3.0f,		// 拡大
			0.0f,		// 回転
			imgsDino_[static_cast<int>(state_)][animNum_],
			true,
			false);
	}
	else // 反転
	{
		// 中心座標で描画
		DrawRotaGraph(
			pos_.x,
			pos_.y,
			3.0f,		// 拡大
			0.0f,		// 回転
			imgsDino_[static_cast<int>(state_)][animNum_],
			true,
			true);
	}
}

// 弾描画
void Enemy::BulletDraw(void)
{
	double angleStep = 30.0 * DX_PI_F / 180.0;
	int circle_num = 360 / 30;

	for (int i = 0; i < circle_num; i++)
	{
		double angle = i * angleStep;

		int x = pos_.x + static_cast<int>(40 * cos(angle));
		int y = pos_.y + static_cast<int>(40 * sin(angle));

		DrawCircle(x, y, 6, 0x0000ff, true);
		DrawCircle(pos_.x, pos_.y, 40, 0xff0000, false);
	}

	////弾の更新および表示
	//for (auto& b : bullets) {
	//	if (!b.isbullet) {
	//		continue;
	//	}

	//	//弾の現在座標に弾の現在速度を加算してください
	//	b.pos.x += b.vel.x;
	//	b.pos.y += b.vel.y;
	//	b.vel.x += b.accel.x;
	//	b.vel.y += b.accel.y;

	//	float angle = atan2f(b.vel.y, b.vel.x);
	//	//弾の角度をatan2で計算してください。angleに値を入れるんだよオゥ
	//	DrawRotaGraph(b.pos.x, b.pos.y, 1.0f, angle, imgBullet_, true);
	//	DrawRotaGraph(pos_.x, pos_.y, 1.0f, 0.0f, imgBullet_, true);

	//	//if (isDebugMode) {
	//	//	//弾の本体(当たり判定)
	//	//	DrawCircle(b.pos.x, b.pos.y, bulletRadius, 0x0000ff, false, 3);
	//	//}
	//	//弾を殺す
	//	if (b.pos.x + 16 < 0 || b.pos.x - 16 > 640 ||
	//		b.pos.y + 24 < 0 || b.pos.y - 24 > 480) {
	//		b.isbullet = false;
	//	}

	//	//if (explosionFrame == 0) {
	//	//	//あたり！
	//	//	//↓のIsHitは実装を書いてません。自分で書いてください。
	//	//	if (IsHit(b.pos, bulletRadius, playerpos, playerRadius)) {
	//	//		//当たった反応を書いてください。
	//	//		b.isActive = false;
	//	//		explosionFrame = 64;
	//	//		hp_--;
	//	//	}
	//	//}
	//}
}

// 移動処理（歩く）
void Enemy::Walk(void)
{
	pos_.x += movePow_;

	// 移動制御（左右に行ったり来たり）
	if (pos_.x > Application::SCREEN_SIZE_X / 2 + 10)
	{
		movePow_ *= -1;
		dir_ = DIR::LEFT;
	}
	else if (pos_.x < Application::SCREEN_SIZE_X / 2 - 10)
	{
		movePow_ *= -1;
		dir_ = DIR::RIGHT;
	}
}

// 移動処理（走る）
void Enemy::Run(void)
{
	pos_.x += movePow_ * 2;

	// 移動制御（左右に行ったり来たり）
	if (pos_.x > Application::SCREEN_SIZE_X / 2 + 10)
	{
		movePow_ *= -1;
		dir_ = DIR::LEFT;
	}
	else if (pos_.x < Application::SCREEN_SIZE_X / 2 - 10)
	{
		movePow_ *= -1;
		dir_ = DIR::RIGHT;
	}
}

void Enemy::Move(void)
{
	if (state_ == ANIM_STATE::WALK)
	{
		Walk();
	}
	else if (state_ == ANIM_STATE::RUN)
	{
		Run();
	}
}

// 発射処理
void Enemy::Shot(void)
{
	////放射状弾
	//float angle = 0.0f;
	//constexpr int dir_count = 8;
	//int count = dir_count;
	//for (auto& b : bullets) {
	//	if (!b.isbullet) {
	//		b.pos = pos_;
	//		angle += (2.0f * DX_PI_F) / (float)dir_count;
	//		b.vel = { cos(angle),sin(angle) };
	//		b.vel.x *= speed;
	//		b.vel.y *= speed;
	//		b.accel = { 0.0f,0.0f };
	//		b.isbullet = true;
	//		--count;
	//		if (count == 0) {
	//			break;
	//		}
	//	}
	//}

}

void Enemy::Debug(void)
{
	if (CheckHitKey(KEY_INPUT_1))
	{
		state_ = ANIM_STATE::IDLE;
	}

	if (CheckHitKey(KEY_INPUT_2))
	{
		state_ = ANIM_STATE::WALK;
	}

	if (CheckHitKey(KEY_INPUT_3))
	{
		state_ = ANIM_STATE::KICK;
	}

	if (CheckHitKey(KEY_INPUT_4))
	{
		state_ = ANIM_STATE::HIT;
	}

	if (CheckHitKey(KEY_INPUT_5))
	{
		state_ = ANIM_STATE::RUN;
	}

	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		dir_ = DIR::RIGHT;
	}
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		dir_ = DIR::LEFT;
	}
}

void Enemy::CollisionHead(void)
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
	//	pos_.y = static_cast<float>(mapPos.y * Stage::CHIP_SIZE_Y + Stage::CHIP_SIZE_Y + SIZE_Y / 2 + hitPos_.y - hitBox_.y);

	//	SetJumpPow(0.0f);
	//}

}

void Enemy::CollisionSide(void)
{
	// 左右の衝突判定（左右の衝突判定）

	// 左の座標
	Vector2 headPosL = GetColPos(COL_LR::L, COL_TD::T);
	// 左の座標
	Vector2 corePosL = GetColPos(COL_LR::L, COL_TD::C);
	// 足元座標（左）
	Vector2 footPosL = GetColPos(COL_LR::L, COL_TD::D);

	/*if (gameScene_->IsCollisionStage(headPosL)
		|| gameScene_->IsCollisionStage(footPosL)
		|| gameScene_->IsCollisionStage(corePosL)
		)
	{
		Vector2 mapPos = gameScene_->World2MapPos(headPosL);
		pos_.x = static_cast<float>(mapPos.x * Stage::CHIP_SIZE_X
			+ Stage::CHIP_SIZE_X + hitBox_.x);

	}

	if (pos_.x > pos_.x + SIZE_X)
	{
		Vector2 mapPos = gameScene_->World2MapPos(headPosL);
		pos_.x = static_cast<float>(mapPos.x * Stage::CHIP_SIZE_X
			+ Stage::CHIP_SIZE_X + hitBox_.x);

	}*/


	// 右の座標
	Vector2 headPosR = GetColPos(COL_LR::R, COL_TD::T);
	// 右の座標
	Vector2 corePosR = GetColPos(COL_LR::R, COL_TD::C);
	// 足元座標（右）
	Vector2 footPosR = GetColPos(COL_LR::R, COL_TD::D);

	//if (gameScene_->IsCollisionStage(headPosR)
	//	|| gameScene_->IsCollisionStage(footPosR)
	//	|| gameScene_->IsCollisionStage(corePosR)
	//	)
	//{
	//	Vector2 mapPos = gameScene_->World2MapPos(headPosR);
	//	pos_.x = static_cast<float>(mapPos.x * Stage::CHIP_SIZE_X
	//		- 1 - hitBox_.x);

	//}

}

Vector2 Enemy::GetColPos(COL_LR lr, COL_TD td)
{
	Vector2 ret = pos_.ToVector2();

	// 相対座標を足す
	ret.x += hitPos_.x;
	ret.y += hitPos_.y;

	// 左右
	switch (lr)
	{
	case Enemy::COL_LR::L:
		ret.x -= hitBox_.x;
		break;
	case Enemy::COL_LR::R:
		ret.x += hitBox_.x;
		break;
	}

	// 上下
	switch (td)
	{
	case Enemy::COL_TD::T:
		ret.y -= hitBox_.y;
		break;
	case Enemy::COL_TD::D:
		ret.y += hitBox_.y;
		break;
	}

	return ret;
}

void Enemy::DrawDebug(void)
{
	//DrawFormatString(0, 0, 0x000000, "プレイヤー座標(%.2f, %.f)", pos_.x, pos_.y);

	//DrawFormatString(0, 20, 0x000000, "移動速度(%.2f)", moveSpeed_);

	//DrawFormatString(0, 40, 0x000000, "ジャンプ力(%.2f)", jumpPow_);

	////Vector2 pos = pos.ToVector2F();

	//DrawBox(pos_.x - SIZE_X / 2, pos_.y - SIZE_Y / 2, pos_.x + SIZE_X / 2, pos_.y + SIZE_Y / 2, 0x000000, false);

	//DrawBox(pos_.x - SIZE_X / 2, pos_.y - SIZE_Y / 2, pos_.x + SIZE_X / 2, pos_.y + SIZE_Y / 2, 0x000000, false);

	//DrawBox(pos.x - 3, pos.y - 3, pos.x + 3, pos.y + 3, 0xff0000, true);

	//// オレンジ
	//int color = 0xff8c00;

	//// デバッグ用：足元衝突判定
	//Vector2 footPos = pos;
	//footPos.y += (8 + 24);

	//// 足元：中央
	//DrawBox(footPos.x - 3, footPos.y - 3, footPos.x + 3, footPos.y + 3, color, true);


	//DrawBox(footPos.x - 3 - 16, footPos.y - 3, footPos.x + 3 - 16, footPos.y + 3, color, true);

	//// デバッグ用：頭の衝突判定
	//Vector2 headPos = pos;
	//headPos.y += (8 - 24);

	//// 頭：中央
	//DrawBox(headPos.x - 3, headPos.y - 3, headPos.x + 3, headPos.y + 3, color, true);
}
