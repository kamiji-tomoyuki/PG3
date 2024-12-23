#include "TitleScene.h"
#include <dinput.h>

void TitleScene::Init()
{
	inputManager_ = InputManager::GetInstance();
}

void TitleScene::Update()
{
	// シーン切り替え
	if (inputManager_->GetPreKey(DIK_SPACE) == 0 && inputManager_->GetKey(DIK_SPACE) != 0) {
		sceneNo = STAGE;
	}
}

void TitleScene::Draw()
{
	Novice::ScreenPrintf(0, 0, "TitleScene");
	Novice::ScreenPrintf(0, 20, "SPACE : StageScene");
}
