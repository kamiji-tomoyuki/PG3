#include "Enemy.h"
#include <stdio.h>

void (Enemy::* Enemy::phaseTable[])() = {
	&Enemy::Approach,
	&Enemy::Shoot,
	&Enemy::Leave
};

void Enemy::Initialize()
{
	phase_ = Phase::Approach;
}

void Enemy::Update()
{
	for (int i = 0; i < 3; i++)
	{
		(this->*phaseTable[static_cast<size_t>(phase_)])();
	}
}

void Enemy::Approach()
{
	// 接近
	printf("接近!!\n\n");

	phase_ = Phase::Shoot;
}

void Enemy::Shoot()
{
	// 射撃
	printf("射撃!!\n\n");

	phase_ = Phase::Leave;
}

void Enemy::Leave()
{
	// 離脱
	printf("離脱!!\n\n");
}
