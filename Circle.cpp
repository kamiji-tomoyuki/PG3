#include "Circle.h"

void Circle::Size()
{
	// 円の面積を計算
	result = rad * rad * pi;
}

void Circle::Draw()
{
	// 求めた値を表示
	printf("円の面積 : %.4f\n", result);
}
