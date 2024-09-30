#include <stdio.h>
int Recursive(int money, int time) {
	if (time <= 1) {
		return money;
	}

	time -= 1;

	return (money + (Recursive(money * 2 - 50, time)));
}

int main() {
	int hours;
	printf("勤務時間：");
	scanf_s("%d/n", &hours);

	int money = 1072;
	printf("一般的な賃金体系：%d\n", money * hours);

	money = 100;
	money = Recursive(money, hours);
	printf("再帰的な賃金体系：%d\n", money);

	return 0;
}