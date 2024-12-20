#pragma once
#include "Windows.h"
#include <cstdint>

#include "imgui.h"

// クライアント領域のサイズ
static const int32_t kClientWidth = 1280;
static const int32_t kClientHeight = 720;

class WinApp
{
public:// 静的メンバ関数
	static LRESULT  CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

public:// メンバ関数
	// 初期化
	void Initialize();

	// 更新
	void Update();

	// 終了
	void Finalize();

	// メッセージの処理
	bool ProcessMessage();

public:
	// getter
	HINSTANCE GetHInstance()const { return wc_.hInstance; }
	HWND GetHwnd()const { return hwnd_; }

private:
	// ウインドウクラスの設定
	WNDCLASS wc_{};
	// ウインドウハンドル
	HWND hwnd_ = nullptr;
};

