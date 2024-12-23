#pragma once
#include "Vector2.h"

class PlayerBullet
{
public:
	void Init(Vector2 pos);
	void Update();
	void Draw();

public:
	bool GetAlive() { return isAlive_; }
	void SetAlive(bool isAlive) { isAlive_ = isAlive; }

	Vector2 GetPos() { return pos_; }
	float GetRad() { return scale_.x; }

private:
	Vector2 pos_;
	Vector2 scale_;
	float speed_;

	bool isAlive_;
};

