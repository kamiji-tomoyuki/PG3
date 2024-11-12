#include "Rectangle.h"

void Rectangle::Size()
{
	// 矩形の面積を計算
	result = side.x * side.y;
}

void Rectangle::Draw()
{
	// 求めた値を表示
	printf("矩形の面積 : %.4f\n", result);
}
