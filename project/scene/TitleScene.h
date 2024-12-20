#pragma once
// 必須
#include <Framework.h>
#include <BaseScene.h>

// 用途に合わせて追加
#include <Audio.h>
#include <Input.h>
#include <Sprite.h>
#include <Object3d.h>

class TitleScene : public BaseScene
{
public:
	// 初期化
	void Initialize() override;

	// 終了
	void Finalize() override;

	// 更新処理
	void Update() override;

	// 描画処理
	void Draw() override;

private: // メンバ変数
	// カメラ
	Camera* camera = nullptr;

	// ===== sample =====
	// スプライト
	Sprite* sprite = nullptr;

	// 3Dオブジェクト
	Object3d* object3d = nullptr;

	// サウンド
	SoundData soundData;
};
