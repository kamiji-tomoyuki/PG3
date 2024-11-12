#pragma once
#include <stdio.h>

class Character
{
public:
	// コンストラクタ・デストラクタ
	Character();
	virtual ~Character();

	// 発表会
	virtual void Recital();

protected:
	// 名前
	const char* name_;
};

