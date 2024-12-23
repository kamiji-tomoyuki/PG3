#include "GameManager.h"

GameManager::GameManager()
{
	inputManager_ = InputManager::GetInstance();
	inputManager_->Init();

	sceneArr_[TITLE] = std::make_unique<TitleScene>();
	sceneArr_[STAGE] = std::make_unique<StageScene>();
	sceneArr_[CLEAR] = std::make_unique<ClearScene>();

	sceneArr_[TITLE]->Init();
}

GameManager::~GameManager()
{
	inputManager_->Finalize();
}

int GameManager::Run()
{
	while (Novice::ProcessMessage() == 0) {
		Novice::BeginFrame();

		inputManager_->Update();

		// シーンチェック
		preSceneNo_ = currentSceneNo_;
		currentSceneNo_ = sceneArr_[currentSceneNo_]->GetSceneNo();

		// 更新チェック
		if (preSceneNo_ != currentSceneNo_) {
			sceneArr_[currentSceneNo_]->Init();
		}

		// 更新
		sceneArr_[currentSceneNo_]->Update();
		// 描画
		sceneArr_[currentSceneNo_]->Draw();

		Novice::EndFrame();

		if (inputManager_->GetPreKey(DIK_ESCAPE) == 0 &&
			inputManager_->GetKey(DIK_ESCAPE) != 0) {
			break;
		}
	}
	return 0;
}
