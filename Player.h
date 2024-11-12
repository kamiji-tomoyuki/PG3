#pragma once
#include "Character.h"

class Player : public Character
{
public:

	Player();
	~Player() override;

	void Recital() override;

};

