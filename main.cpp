#include <stdio.h>

#include <chrono>   
#include <thread>
#include <time.h>   

int DiceRoll() {
    // ランダムな値を出す
    return rand() % 6 + 1;
}

int Search(int number) {
    // 奇数か偶数かを判定
    if (number % 2 == 0) {
        return 0;
    }
    else {
        return 1;
    }
}

void Result(bool correct, void (*callback)(), int dice) {
    // 3秒待機
    callback();

    // 正解 or 不正解 を表示
    printf("サイコロは「%d 」を出しました\n", dice);
    if (correct) {
        printf("正解だよ\n");
    }
    else {
        printf("不正解だよ\n");
    }
}

void SetTimeout() {
    // 3秒待つ！
    std::this_thread::sleep_for(std::chrono::seconds(3));
}

int main() {
    srand(time(0));

    printf("奇数(1) or 偶数(0)？ : ");

    // 予想を書き込む
    int forecast;
    scanf_s("%d", &forecast);

    // ランダムな値を取得
    int dice = DiceRoll();
    // 判定！
    int search = Search(dice);

    //予想と結果を比較する
    bool correct = (forecast == search);

    // 3秒待機後、結果を表示
    Result(correct, SetTimeout, dice);

    return 0;
}