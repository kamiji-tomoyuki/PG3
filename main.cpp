#include <stdio.h>

#include "Player.h"
#include "Audience.h"

int main() {
    const int num = 2;
	Character* character[num];

    // 生成
	printf("今日はピアノの発表会\n\n");
    for (int i = 0; i < num; ++i)
    {
        if (i == 0)
        {
            character[i] = new Player;
        }
        else
        {
            character[i] = new Audience;
        }
    }

    // 演奏
    printf("\n演奏が始まった..!\n\n");
    for (int i = 0; i < num; ++i)
    {
       character[i]->Recital();
    }

    // 解放
    printf("\n演奏が終わった！\n\n");
    for (int i = 0; i < num; ++i)
    {
        delete character[i];
    }

    return 0;
}