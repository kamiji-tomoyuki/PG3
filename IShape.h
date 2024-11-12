#pragma once
#include <stdio.h>

struct Vector2
{
	float x;
	float y;
};

class IShape
{
public:
	// 面積を求める
	virtual void Size() = 0;
	// 値を表示
	virtual void Draw() = 0;
};

