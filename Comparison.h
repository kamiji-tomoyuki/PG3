#pragma once

template <typename T>

class Comparison {
public:

	T num1_, num2_;
	Comparison(T num1, T num2) :num1_(num1), num2_(num2) {};

	// 二つの値を比較、小さいほうを返す
	T Min(T num1, T num2)
	{
		return static_cast<T>(num1_ < num2_ ? num1_ : num2_);
	};

};