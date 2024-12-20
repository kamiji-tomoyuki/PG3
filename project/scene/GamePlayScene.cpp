#include "GamePlayScene.h"

void GamePlayScene::Initialize()
{
	// --- カメラ ---
	camera = new Camera();
	camera->SetRotate({ 0.3f,0.0f,0.0f });
	camera->SetTranslate({ 0.0f,4.0f,-10.0f });
	Object3dCommon::GetInstance()->SetDefaultCamera(camera);

	// --- サンプル ---
	sample = std::make_unique<Sample>();
	sample->Initialize();

	// --- オーディオ ---
	// 音声データ読み込み (「 Resources / audio 」は省略 )
	soundDataSet = Audio::GetInstance()->LoadWav("mokugyo.wav");
	// 再生
	Audio::GetInstance()->PlayWave(soundDataSet, true, 0.02f);	// ( 音声データ変数, ループ, ボリューム ( 0 ~ 1 ) );

	soundDataSet2 = Audio::GetInstance()->LoadWav("test/xxx.wav");
	Audio::GetInstance()->PlayWave(soundDataSet2, false, 0.01f);
}

void GamePlayScene::Finalize()
{
	// 各解放処理
	delete camera;
	Object3dCommon::GetInstance()->Finalize();
}

void GamePlayScene::Update()
{
	//カメラの更新
	camera->Update();

	// サンプルクラス更新
	sample->Update();
}

void GamePlayScene::Draw()
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

	sample->Draw();

	// ↑ ↑ ↑ ↑ Draw を書き込む ↑ ↑ ↑ ↑
#pragma endregion
}