#include "TitleScene.h"

void TitleScene::Initialize()
{
	// --- カメラ ---
	camera = new Camera();
	camera->SetRotate({ 0.3f,0.0f,0.0f });
	camera->SetTranslate({ 0.0f,4.0f,-10.0f });
	Object3dCommon::GetInstance()->SetDefaultCamera(camera);

	// ===== sample =====
	// --- スプライト ---
	// スプライト名の指定 (Initializeに直接入れても可)
	std::string textureFile = "monsterBall.png";
	// 生成・初期化
	sprite = new Sprite();
	sprite->Initialize(textureFile, { 0,0 }, { 1,1,1,1 }, { 0,0 });	// (スプライト名, 座標, 色, アンカーポイント);

	// --- オブジェクト ---
	//

	inputHandler_ = new InputHandler();
	inputHandler_->AssignMoveRightCommand2PressKeyA();
	inputHandler_->AssignMoveLeftCommand2PressKeyA();

	player_ = new Player();
	player_->Init();
}

void TitleScene::Finalize()
{
	// 各解放処理
	delete camera;

	// ===== sample =====
	delete sprite;
	Audio::GetInstance()->SoundUnload(Audio::GetInstance()->GetXAudio2(), &soundData);

	delete inputHandler_;
	delete player_;
}

void TitleScene::Update()
{
	// カメラの更新
	camera->Update();

	// ===== sample =====
	// スプライト ( ↓ 変更可能ステータス ↓ )
	// 座標
	Vector2 position = { 0.0f, 0.0f };
	sprite->SetPosition(position);
	// 回転
	float rotation = sprite->GetRotate();
	sprite->SetRotate(rotation);
	// スケール
	Vector2 size = { 200.0f,200.0f };
	sprite->SetSize(size);
	// 色
	Vector4 color = sprite->GetColor();
	sprite->SetColor(color);

	// ============================================

	iCommand_ = inputHandler_->HandleInput();

	if (this->iCommand_) {
		iCommand_->Exec(*player_);
	}

	player_->Update();

	// ============================================

	// --- シーン移行処理 ---
	// ENTERキーを押した時
	if (Input::GetInstance()->TriggerKey(DIK_RETURN)) {
		// 次のシーンを生成
		SceneManager::GetInstance()->ChangeScene("GAMEPLAY");
	}
}

void TitleScene::Draw()
{
#pragma region 背景 Sprite
	// ========== 背景 Sprite 描画 ==========
	// 描画前処理 (Sprite)
	SpriteCommon::GetInstance()->PreDraw();
	// ↓ ↓ ↓ ↓ Draw を書き込む ↓ ↓ ↓ ↓



	// ↑ ↑ ↑ ↑ Draw を書き込む ↑ ↑ ↑ ↑
#pragma endregion

#pragma region Model
	// ==========    Model 描画    ==========
	// 描画前処理 (Object)
	Object3dCommon::GetInstance()->PreDraw();
	// ↓ ↓ ↓ ↓ Draw を書き込む ↓ ↓ ↓ ↓



	// ↑ ↑ ↑ ↑ Draw を書き込む ↑ ↑ ↑ ↑
#pragma endregion

#pragma region 前景 Sprite
	// ========== 前景 Sprite 描画 ==========
	// 描画前処理 (Sprite)
	SpriteCommon::GetInstance()->PreDraw();

	// ↓ ↓ ↓ ↓ Draw を書き込む ↓ ↓ ↓ ↓

	// ===== sample =====
	//sprite->Draw();
	//Draw2D::GetInstance()->DrawBox({ kClientWidth / 2 , kClientHeight / 2 }, { 100.0f,100.0f }, { 1.0f, 1.0f, 1.0f, 1.0f });
	//Draw2D::GetInstance()->DrawLine({ 0.0f,0.0f }, { 200.0f,200.0f }, { 1.0f, 1.0f, 1.0f, 1.0f });

	player_->Draw();

	// ↑ ↑ ↑ ↑ Draw を書き込む ↑ ↑ ↑ ↑
#pragma endregion
}
