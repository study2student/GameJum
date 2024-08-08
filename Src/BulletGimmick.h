#pragma once
#include "Common/Vector2F.h"

class BulletGimmick
{

public:

	BulletGimmick(void);

	~BulletGimmick(void);

	void Init(void);

	void Update(void);
	
	void Draw(void);

	void Release(void);

private:

	Vector2F pos_;

};