#include <DxLib.h>
#include <cmath> 
#include "Manager/InputManager.h"
#include "Common/Vector2.h"
#include "Application.h"
#include "SceneBase/GameScene.h"
#include "Player/Player.h"
#include "Enemy.h"

Enemy::Enemy(void)
{
}

Enemy::~Enemy(void)
{
}

void Enemy::Init(GameScene* scene_)
{
	gameScene_ = scene_;


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
		(basePath + "Enemy/cloud.png").c_str(),
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
	speedAnim_ = 0.05f;
	animNum_ = 0;

	// 敵の座標
	pos_ = { Application::SCREEN_SIZE_X /2,Application::SCREEN_SIZE_Y /2 - 200};
	// 敵の状態
	state_ = ANIM_STATE::IDLE;
	atkState_ = ATK_STATE::NONE;
	dir_ = DIR::RIGHT;

	// 敵の移動量
	movePow_ = 0.5f;

	// 衝突判定用：中心座標（pos_からの相対座標）
	hitPos_ = { 0, 0};

	// 衝突判定用：範囲
	hitBox_ = { 34, 34 };

	// ランダム用
	blink_ = 0;
	rand_ = 0;

	stateRand_ = false;

	bulletPow_ = { 0,0 };
	bulletPos_ = { 0,0 };
	isBullet_ = false;
}

void Enemy::Update(void)
{
	auto& ins = InputManager::GetInstance();

	cntAnim_++;

	// 移動処理
	Move();

	// ランダムで状態を切り替え
	RandState();

	//switch (state_)
	//{
	//case ANIM_STATE::IDLE:
	//	animNum_ = static_cast<int>(
	//		static_cast<float>(cntAnim_) * speedAnim_)
	//		% IDLE_ANIM_NUM;

	//	break;

	//case ANIM_STATE::WALK:
	//	animNum_ = static_cast<int>(
	//		static_cast<float>(cntAnim_) * speedAnim_)
	//		% WALK_ANIM_NUM;

	//	break;	
	//
	//case ANIM_STATE::KICK:
	//	animNum_ = static_cast<int>(
	//		static_cast<float>(cntAnim_) * speedAnim_)
	//		% KICK_ANIM_NUM;
	//	if (animNum_ == 3) {
	//		state_ = ANIM_STATE::IDLE;
	//		break;
	//	}

	//case ANIM_STATE::HIT:
	//	animNum_ = static_cast<int>(
	//		static_cast<float>(cntAnim_) * speedAnim_)
	//		% HIT_ANIM_NUM;
	//	break;

	//case ANIM_STATE::RUN:
	//	animNum_ = static_cast<int>(
	//		static_cast<float>(cntAnim_) * speedAnim_)
	//		% RUN_ANIM_NUM;

	//	break;

	//default:
	//	break;
	//}
	elapsedTime = 0;

	if (isBullet_ == true)
	{
		elapsedTime++;
		Shot();
	}

	//攻撃(未実装)
	atkState_ = ATK_STATE::NONE;		//基本は攻撃していない
	if (isBullet_ == false
		&& CheckHitKey(KEY_INPUT_N))
	{
		atkState_ = ATK_STATE::SHOT;
		isBullet_ = true;
	}
}

void Enemy::Draw(void)
{
	EnemyDraw();

	if (isBullet_ == true)
	{
		BulletDraw();
	}

	DrawDebug();
	
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
	// 座標変換
	Vector2 pos = pos_.ToVector2();

	if (dir_ == DIR::RIGHT)
	{
		// 中心座標で描画
		DrawRotaGraph(
			pos.x,
			pos.y,
			4.0f,		// 拡大
			0.0f,		// 回転
			imgsDino_[static_cast<int>(state_)][animNum_],
			true,
			false);
	}
	else // 反転
	{
		// 中心座標で描画
		DrawRotaGraph(
			pos.x,
			pos.y,
			4.0f,		// 拡大
			0.0f,		// 回転
			imgsDino_[static_cast<int>(state_)][animNum_],
			true,
			true);
	}
}

// 弾描画
void Enemy::BulletDraw(void)
{
	double angleStep = 60.0 * DX_PI_F / 180.0;
	int circle_num = 6;

	for (int i = 0; i < circle_num; i++)
	{
		double angleC = i * angleStep;

		bulletPos_.x = pos_.x + static_cast<int>(bulletPow_.x * cos(angleC));
		bulletPos_.y = pos_.y + static_cast<int>(bulletPow_.y * sin(angleC));

		DrawCircle(bulletPos_.x, bulletPos_.y, 6, 0x0000ff, true);
		//DrawCircle(pos_.x, pos_.y, 40, 0xff0000, false);
		DrawCircle(bulletPos_.x, bulletPos_.y, 6, 0xff00ff, false);
	}
}

// 移動処理（歩く）
void Enemy::Walk(void)
{
	pos_.x += movePow_;
}

// 移動処理（走る）
void Enemy::Run(void)
{
	pos_.x += movePow_ * 2;
}

// 移動処理
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

	// 移動制御（左右に行ったり来たり）
	if (pos_.x > Application::SCREEN_SIZE_X / 2 + 250)
	{
		movePow_ *= -1;
		dir_ = DIR::LEFT;
	}
	else if (pos_.x < Application::SCREEN_SIZE_X / 2 - 250)
	{
		movePow_ *= -1;
		dir_ = DIR::RIGHT;
	}
}

void Enemy::ShotActive(void)
{
	atkState_ = ATK_STATE::SHOT;
	isBullet_ = true;
}

// 発射処理
void Enemy::Shot(void)
{
	int time = GetTime(); 

	++bulletPow_.x;
	++bulletPow_.y;

	//7秒経つと消えるように
	if ((time / 1000) % 7 == 0)
	{
		bulletPow_ = { 0,0 };
		time = 0;
		atkState_ = ATK_STATE::NONE;
		isBullet_ = false;
		return;
	}
}

Vector2F Enemy::GetEnemyPos(void)
{
	return pos_;
}

void Enemy::SetEnemyPos(Vector2F value)
{
	pos_ = value;
}

Vector2 Enemy::GetBulletPow(void)
{
	return bulletPow_;
}



Vector2 Enemy::GetBulletPos(void)
{
	return bulletPos_;
}

void Enemy::SetBulletPos(Vector2F value)
{
	bulletPos_ = value;
}

// キーを押下すると状態切り替え
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
	DrawFormatString(700, 0, 0x000000, "Bullet座標(%d, %d)", bulletPos_.x,bulletPos_.y);
	DrawFormatString(800, 20, 0x000000, "radom(%d)", rand_);


	Vector2 pos = pos.ToVector2F();

	DrawBox(pos_.x - SIZE_X - 10, pos_.y - SIZE_Y - 10, pos_.x + SIZE_X + 10, pos_.y + SIZE_Y + 10, 0xff0000, false);
	DrawBox(pos_.x - SIZE_X - 10, pos_.y + SIZE_Y + 250, pos_.x + SIZE_X + 10, pos_.y + SIZE_Y + 300, 0xff00ff, false);

}

// ランダムに状態が切り替わる
void Enemy::RandState(void)
{
	int time = GetTime();

	if ((time / 1000) % 3 == 0)
	{

		if (!stateRand_)
		{
			rand_ = GetRand(100);
		}
		stateRand_ = true;
	}
	else
	{
		stateRand_ = false;
	}

	if (rand_ > 90)
	{
		state_ = ANIM_STATE::IDLE;
	}
	else if (rand_ > 60)
	{
		state_ = ANIM_STATE::WALK;
	}
	else if(rand_ > 30)
	{
		state_ = ANIM_STATE::KICK;
	}
	else
	{
		state_ = ANIM_STATE::RUN;
	}

	switch (state_)
	{
	case ANIM_STATE::IDLE:
		animNum_ = static_cast<int>(
			static_cast<float>(cntAnim_) * speedAnim_)
			% IDLE_ANIM_NUM;
		cntAnim_++;

		blink_ = 0;
		break;

	case ANIM_STATE::WALK:
		animNum_ = static_cast<int>(
			static_cast<float>(cntAnim_) * speedAnim_)
			% WALK_ANIM_NUM;

		cntAnim_++;

		if (animNum_ > 5)
		{
			rand_ = 100;
			state_ = ANIM_STATE::IDLE;
		}

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

		cntAnim_++;

		break;

	case ANIM_STATE::RUN:
		animNum_ = static_cast<int>(
			static_cast<float>(cntAnim_) * speedAnim_)
			% RUN_ANIM_NUM;

		if (animNum_ == 0)
		{
			blink_++;
		}
		if (blink_ > 4 && animNum_ == 6)
		{
			rand_ = 100;
			state_ = ANIM_STATE::IDLE;
		}
		break;

	default:
		break;
	}
}

// 経過時間を返す
int Enemy::GetTime(void)
{
	elapsedTime = (GetNowCount() - startTime);

	return elapsedTime;
}