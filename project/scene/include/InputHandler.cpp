#include "InputHandler.h"
#include "Input.h"

ICommand* InputHandler::HandleInput()
{
	if (Input::GetInstance()->PushKey(DIK_D)) {
		return pressKeyD_;
	}
	if (Input::GetInstance()->PushKey(DIK_A)) {
		return pressKeyA_;
	}

	return nullptr;
}

void InputHandler::AssignMoveRightCommand2PressKeyA()
{
	ICommand* command = new MoveRightCommand();
	this->pressKeyD_ = command;
}

void InputHandler::AssignMoveLeftCommand2PressKeyA()
{
	ICommand* command = new MoveLeftCommand();
	this->pressKeyA_ = command;
}
