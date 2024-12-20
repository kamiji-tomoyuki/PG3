#pragma once
#include <Windows.h>
#include <Camera.h>
#include <D3DResourceLeakChecker.h>
#include <DirectXCommon.h>
#include <ImGuiManager.h>
#include <SceneFactory.h>
#include <WinApp.h>

#include <Draw2D.h>
#include <ModelManager.h>
#include <Object3dCommon.h>
#include <SceneManager.h>
#include <SpriteCommon.h>
#include <SrvManager.h>
#include <TextureManager.h>

// フレームワーク
class Framework
{
public:
	virtual ~Framework() = default;

	// 実行
	void Run();

	// 初期化
	virtual void Initialize();

	// 終了
	virtual void Finalize();

	// 更新処理
	virtual void Update();

	// 描画処理
	virtual void Draw() = 0;

	// 終了リクエストの取得
	virtual bool IsEndRequest() { return winApp->ProcessMessage(); }

protected:
	// 汎用性の高いシステム
	WinApp* winApp = nullptr;					// WindowsAPI
	DirectXCommon* dxCommon = nullptr;			// DirectX

	ImGuiManager* imGuiManager = nullptr;		// ImGuiマネージャ

	AbstractSceneFactory* 
		sceneFactory_ = nullptr;				// シーンファクトリー
};

