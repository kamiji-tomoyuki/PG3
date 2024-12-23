#include "Player.h"
#include <Novice.h>

void Player::Init()
{
	inputManager_ = InputManager::GetInstance();

	pos_ = { 640.0f,500.0f };
	scale_ = { 30.0f,30.0f };
	speed_ = 5.0f;
}

void Player::Update()
{
	Move();
	Shot();

	for (auto& bullet : bullets_) {
		bullet->Update();
	}
}

void Player::Draw()
{
	Novice::DrawBox(
		int(pos_.x - (scale_.x / 2)),
		int(pos_.y - (scale_.y / 2)),
		(int)scale_.x,
		(int)scale_.y,
		0.0f,
		WHITE,
		kFillModeSolid);

	for (auto& bullet : bullets_) {
		bullet->Draw();
	}
}

void Player::Move()
{
	if (inputManager_->GetKey(DIK_W)) {
		pos_.y -= speed_;
	}
	if (inputManager_->GetKey(DIK_S)) {
		pos_.y += speed_;
	}
	if (inputManager_->GetKey(DIK_D)) {
		pos_.x += speed_;
	}
	if (inputManager_->GetKey(DIK_A)) {
		pos_.x -= speed_;
	}
}

void Player::Shot()
{
	if (inputManager_->GetPreKey(DIK_SPACE) == 0 && inputManager_->GetKey(DIK_SPACE) != 0) {
		std::unique_ptr<PlayerBullet> bullet;
 		bullet = std::make_unique<PlayerBullet>();
		bullet->Init(pos_);
		bullets_.push_back(std::move(bullet));
	}
}
