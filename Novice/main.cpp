#include <Novice.h>
#include <Vector2.h>
#include <class/GameManager.h>

const char kWindowTitle[] = "PG3_LE2B_07_カミジ_トモユキ";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// ------------------------------------------------

	std::unique_ptr<GameManager> gameManager_;
	gameManager_ = std::make_unique<GameManager>();

	gameManager_->Run();

	// ------------------------------------------------

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
