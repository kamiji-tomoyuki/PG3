#include "Player.h"

void Player::Init()
{
	std::string textureFile = "monsterBall.png";
	sprite = std::make_unique<Sprite>();
	sprite->Initialize(textureFile, { 0,0 }, { 1,1,1,1 }, { 0,0 });
	sprite->SetPosition(pos_);
	sprite->SetSize({ 50.0f,50.0f });
}

void Player::Update()
{
	sprite->SetPosition(pos_);
}

void Player::Draw()
{
	sprite->Draw();
}

void Player::MoveLeft()
{
	this->pos_.x -= this->speed_;
}

void Player::MoveRight()
{
	this->pos_.x += this->speed_;
}
