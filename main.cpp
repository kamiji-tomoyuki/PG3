#include <stdio.h>

#include "Circle.h"
#include "Rectangle.h"

int main() {
	const int num = 2;
	IShape* iShape[num];

    // 生成
    for (int i = 0; i < num; ++i)
    {
        if (i < 1)
        {
            // 円
            iShape[i] = new Circle();
        }
        else
        {
            // 矩形
            iShape[i] = new Rectangle();
        }
    }

    // 計算・表示
    for (int i = 0; i < num; ++i)
    {
        iShape[i]->Size();

        iShape[i]->Draw();
    }


	return 0;
}