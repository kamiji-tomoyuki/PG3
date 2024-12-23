#pragma once
#include <vector>

#include "PlayerBullet.h"

class Enemy
{
public:
	void Init();
	void Update();
	void Draw();

private:
	void Hit();

public:
	bool GetAlive() { return isAlive_; }

	void SetBullet(const std::vector<PlayerBullet*>& bullets) { bullets_ = bullets; }

private:
	std::vector<PlayerBullet*> bullets_;

	Vector2 pos_;
	Vector2 scale_;
	float speed_;

	bool isAlive_;
};

