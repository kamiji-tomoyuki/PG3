#pragma once
#include "InputManager.h"

enum SCENE { TITLE, STAGE, CLEAR };

class IScene
{
protected:
	InputManager* inputManager_;
	static int sceneNo;

public:
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	virtual ~IScene();

	int GetSceneNo();
};

