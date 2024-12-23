#include "StageScene.h"
#include <dinput.h>

void StageScene::Init()
{
	inputManager_->GetInstance();

	player_ = std::make_unique<Player>();
	player_->Init();

	enemy_ = std::make_unique<Enemy>();
	enemy_->Init();

	isClear = false;
}

void StageScene::Update()
{
	player_->Update();

	enemy_->SetBullet(player_->GetBullet());
	enemy_->Update();

	if (!enemy_->GetAlive()) {
		sceneNo = CLEAR;
	}
}

void StageScene::Draw()
{
	Novice::ScreenPrintf(0, 0, "StageScene");
	Novice::ScreenPrintf(0, 20, "WASD : Move");
	Novice::ScreenPrintf(0, 35, "SPACE : Shot!");
	player_->Draw();
	enemy_->Draw();
}
