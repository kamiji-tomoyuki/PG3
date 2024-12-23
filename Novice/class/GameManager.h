#pragma once
#include <memory>
#include <Novice.h>
#include "InputManager.h"
#include "IScene.h"
#include "scene/TitleScene.h"
#include "scene/StageScene.h"
#include "scene/ClearScene.h"

class GameManager
{
private:
	InputManager* inputManager_;
	std::unique_ptr<IScene> sceneArr_[3];

	// 現在のシーン
	int currentSceneNo_ = 0;
	// 前のシーン
	int preSceneNo_ = 0;

public:
	GameManager();
	~GameManager();

	int Run();
};

