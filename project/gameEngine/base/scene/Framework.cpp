#include "Framework.h"
#include <imgui.h>

void Framework::Run()
{
	// ===== 初期化処理 =====
	Initialize();

	while (true) {
		// 終了リクエストが来たら抜ける
		if (IsEndRequest()) {
			break;
		}
		// ===== 更新処理 =====
#ifdef _DEBUG
		// ImGui開始
		imGuiManager->Begin();
#endif // _DEBUG

		// 毎フレーム更新
		Update();

#ifdef _DEBUG
		// ImGui終了
		imGuiManager->End();
#endif // _DEBUG

		// ===== 描画処理 =====

		// 描画
		Draw();
	}

	// ===== 解放処理 =====
	Finalize();
}

void Framework::Initialize()
{
	// --- ウィンドウの初期化 ---
	// WindowsAPI
	winApp = new WinApp();
	winApp->Initialize();

	// --- 基盤システムの初期化 ---
	// DirectX
	dxCommon = new DirectXCommon();
	dxCommon->Initialize(winApp);

#ifdef _DEBUG
	// ImGui
	imGuiManager = new ImGuiManager();
	imGuiManager->Initialize(winApp, dxCommon);
#endif

	// SRVマネージャ
	SrvManager::GetInstance()->Initialize(dxCommon);

	// テクスチャマネージャ
	TextureManager::GetInstance()->Initialize(dxCommon);

	// モデルマネージャ
	ModelManager::GetInstance()->Initialize(dxCommon);

	// 3Dオブジェクト
	Object3dCommon::GetInstance()->Initialize(dxCommon);

	// 2D描画
	Draw2D::GetInstance()->Initialize(dxCommon);

	// スプライト
	SpriteCommon::GetInstance()->Initialize(dxCommon);

	// シーンマネージャ
	SceneManager::GetInstance();
}

void Framework::Update()
{
	// シーンマネージャの更新
	SceneManager::GetInstance()->Update();
}

void Framework::Finalize()
{
	SrvManager::GetInstance()->Finalize();

	TextureManager::GetInstance()->Finalize();

	ModelManager::GetInstance()->Finalize();

	Object3dCommon::GetInstance()->Finalize();

	Draw2D::GetInstance()->Finalize();

	SpriteCommon::GetInstance()->Finalize();

	SceneManager::GetInstance()->Finalize();

#ifdef _DEBUG
	imGuiManager->Finalize();
	delete imGuiManager;
#endif

	delete dxCommon;

	delete sceneFactory_;

	winApp->Finalize();
	delete winApp;
}

