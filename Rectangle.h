#pragma once
#include "IShape.h"

class Rectangle : public IShape
{
public:
	void Size() override;
	void Draw() override;

private:
	Vector2 side = { 5.0f,3.0f };
	float result = 0;
};

