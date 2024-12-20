#pragma once
#include <Vector2.h>
#include <Sprite.h>

class Player
{
public:
	void Init();
	void Update();
	void Draw();

	void MoveLeft();
	void MoveRight();

private:
	std::unique_ptr<Sprite> sprite;

	Vector2 pos_ = { 10.0f,10.0f };
	float speed_ = 1.0f;
};