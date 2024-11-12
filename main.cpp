#include <stdio.h>

#include "Comparison.h"

int main() {
	// --- int型 ---
	int numInt1 = 10;
	int numInt2 = 30;

	// 比較
	Comparison<int> resultInt(numInt1, numInt2);
	int resultNumInt = resultInt.Min(resultInt.num1_, resultInt.num2_);
	printf("int , int : %d\n", resultNumInt);


	// --- float型 ---
	float numFloat1 = 35.5f;
	float numFloat2 = 36.5f;

	// 比較
	Comparison<float> resultFloat(numFloat1, numFloat2);
	float resultNumFloat = resultFloat.Min(resultFloat.num1_, resultFloat.num2_);
	printf("float , float : %f\n", resultNumFloat);


	// --- double型 ---
	double numDouble1 = 99.9f;
	double numDouble2 = 10.1f;

	// 比較
	Comparison<double> resultDouble(numDouble1, numDouble2);
	double resultNumDouble = resultDouble.Min(resultDouble.num1_, resultDouble.num2_);
	printf("double , double : %f\n", resultNumDouble);


	return 0;
}