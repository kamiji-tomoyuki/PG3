#include "InputManager.h"
#include <Novice.h>
#include <dinput.h>

InputManager* InputManager::instance = nullptr;

InputManager* InputManager::GetInstance()
{
	if (instance == nullptr) {
		instance = new InputManager;
	}
	return instance;
}

void InputManager::Finalize()
{
	delete instance;
	instance = nullptr;
}

void InputManager::Init()
{
	memset(preKeys, 0, sizeof(preKeys));
	memset(keys, 0, sizeof(keys));
}

void InputManager::Update()
{
	memcpy(preKeys, keys, sizeof(preKeys));
	Novice::GetHitKeyStateAll(keys);
}

bool InputManager::GetPreKey(char keyCode)
{
	return preKeys[keyCode] != 0;
}

bool InputManager::GetKey(char keyCode)
{
	return keys[keyCode] != 0;
}
