#pragma once
#include <memory>
#include <vector>

#include "Vector2.h"
#include "../InputManager.h"
#include "PlayerBullet.h"

class Player
{
public:
	void Init();
	void Update();
	void Draw();

private:
	void Move();
	void Shot();

public:
	std::vector<PlayerBullet*> GetBullet() {
		std::vector<PlayerBullet*> bulletPtrs;
		for (const auto& bullet : bullets_) {
			bulletPtrs.push_back(bullet.get());
		}
		return bulletPtrs;
	}

private:
	InputManager* inputManager_;

	// ステータス
	Vector2 pos_;
	Vector2 scale_;
	float speed_;

	// 弾
	std::vector<std::unique_ptr<PlayerBullet>> bullets_;
};

