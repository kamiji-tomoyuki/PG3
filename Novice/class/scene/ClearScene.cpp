#include "ClearScene.h"
#include <dinput.h>

void ClearScene::Init()
{
	inputManager_ = InputManager::GetInstance();
}

void ClearScene::Update()
{
	if (inputManager_->GetPreKey(DIK_SPACE) == 0 && inputManager_->GetKey(DIK_SPACE) != 0) {
		sceneNo = TITLE;
	}
}

void ClearScene::Draw()
{
	Novice::ScreenPrintf(0, 0, "ClearScene");
	Novice::ScreenPrintf(0, 20, "SPACE : TitleScene");
}
