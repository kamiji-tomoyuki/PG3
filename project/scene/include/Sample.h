#pragma once
#include <memory>

#include <Sprite.h>
#include <Object3d.h>

// サンプル
class Sample
{
public:
	// 初期化
	void Initialize();

	// 更新処理
	void Update();

	// 描画処理
	void Draw();

private:
	// Sprite更新処理
	void UpdateSprite();

	// Object3d更新処理
	void UpdateObj();

private:
	// 2Dスプライト
	std::unique_ptr<Sprite> sprite;

	// 3Dオブジェクト
	std::unique_ptr<Object3d> object3d;
};

