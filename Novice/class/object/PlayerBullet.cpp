#include "PlayerBullet.h"
#include <Novice.h>

void PlayerBullet::Init(Vector2 pos)
{
	pos_ = pos;
	scale_ = { 8.0f, 8.0f };
	isAlive_ = true;
}

void PlayerBullet::Update()
{
	if (isAlive_) {
		speed_ = -7.0f;
 		pos_.y += speed_;
	}
}

void PlayerBullet::Draw()
{
	if (isAlive_) {
		Novice::DrawEllipse(
			int(pos_.x),
			int(pos_.y),
			(int)scale_.x,
			(int)scale_.y,
			0.0f,
			WHITE,
			kFillModeSolid);
	}
}
