#include "MyGame.h"

#include <Audio.h>
#include <Input.h>
#include <SceneFactory.h>

void MyGame::Initialize()
{
	// --- 基底クラスの初期化 ---
	Framework::Initialize();

	// --- シーンの生成・初期化 ---
	// シーンマネージャに最初のシーンをセット	
	sceneFactory_ = new SceneFactory();
	SceneManager::GetInstance()->SetSceneFactory(sceneFactory_);

	// --- 汎用機能の初期化 ---
	// キーボード入力
	Input::GetInstance()->Initialize(winApp);
	// オーディオ
	Audio::GetInstance()->Initialize();

	// 最初のシーンを設定
	SceneManager::GetInstance()->ChangeScene("TITLE");
	
}

void MyGame::Finalize()
{
	// --- リークチェック ---
	D3DResourceLeakChecker leakCheck;

	Framework::Finalize();	// 基底クラスの解放処理
	
	Audio::GetInstance()->Finalize();
	Input::GetInstance()->Finalize();
}

void MyGame::Update()
{
	// --- 基底クラスの更新処理 ---
	Framework::Update();

	// キーボード入力
	Input::GetInstance()->Update();
}

void MyGame::Draw()
{
	// 描画前処理 (SRV)
	SrvManager::GetInstance()->PreDraw();

	// 描画前処理 (DirectX)
	dxCommon->PreDraw();

	// --- シーンの描画処理 ---

	SceneManager::GetInstance()->Draw();
	Draw2D::GetInstance()->Reset();

	// ----------------------

#ifdef _DEBUG
	imGuiManager->Draw();
#endif // _DEBUG

	// 描画後処理
	dxCommon->PostDraw();
}
