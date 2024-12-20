#pragma once
#include "command.h"

class InputHandler
{
public:
	ICommand* HandleInput();

	void AssignMoveRightCommand2PressKeyA();
	void AssignMoveLeftCommand2PressKeyA();

private:
	ICommand* pressKeyD_;
	ICommand* pressKeyA_;
};

