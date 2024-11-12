#pragma once
#include "Character.h"

class Audience : public Character
{
public:

	Audience();
	~Audience() override;

	void Recital() override;

};

