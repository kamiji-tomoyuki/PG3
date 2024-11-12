#pragma once
#include "IShape.h"

class Circle : public IShape
{
public:
	void Size() override;
	void Draw() override;

private:
	float rad = 4.0f;
	const float pi = 3.14159f;
	float result = 0;
};

