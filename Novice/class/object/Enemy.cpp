#include "Enemy.h"
#include <Novice.h>

#include "math/CalculateMath.h"

void Enemy::Init()
{
	isAlive_ = true;

	pos_ = { 100.0f,100.0f };
	scale_ = { 25.0f,25.0f };
	speed_ = 3.0f;
}

void Enemy::Update()
{
	if (isAlive_) {
		pos_.x += speed_;
		if (pos_.x < 100 || pos_.x > 1180) {
			speed_ *= -1.0f;
		}
	}

	Hit();
}

void Enemy::Draw()
{
	if (isAlive_) {
		Novice::DrawEllipse(
			int(pos_.x - (scale_.x / 2)),
			int(pos_.y - (scale_.y / 2)),
			(int)scale_.x,
			(int)scale_.y,
			0.0f,
			RED,
			kFillModeSolid);
	}
}

void Enemy::Hit()
{
	for (auto bullet : bullets_) {
		Vector2 temp = { bullet->GetPos().x - pos_.x,bullet->GetPos().y - pos_.y };
		float distance = Length(temp);

		if (distance < (bullet->GetRad() + scale_.x)) {
			bullet->SetAlive(false);
			isAlive_ = false;
		}
	}
}
