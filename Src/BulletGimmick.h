#pragma once
#include <vector>
#include "Common/Vector2F.h"

class Bullet;

class BulletGimmick
{

public:

	BulletGimmick(void);

	~BulletGimmick(void);

	void Init(void);

	void Update(void);
	
	void Draw(void);

	void Release(void);

	// ’e‚Ìƒf[ƒ^‚Ìæ“¾
	std::vector<Bullet*> GetBulletData(void);

private:

	std::vector<Bullet*> bullet_;

	Bullet* GetAvailableShot(void);

};