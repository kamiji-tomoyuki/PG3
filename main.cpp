#include <stdio.h>

#include "Enemy.h"

int main() {
	// 生成
	Enemy* enemy = nullptr;
	enemy = new Enemy();

	// 初期化
	enemy->Initialize();

	// 更新
	enemy->Update();


	return 0;

	// 解放
	delete enemy;
}