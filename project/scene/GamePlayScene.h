#pragma once
#include <Framework.h>
#include <BaseScene.h>

#include <Audio.h>

#include "Sample.h"

class GamePlayScene : public BaseScene
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

	// サンプルクラス
	std::unique_ptr<Sample> sample;

	// サウンド
	SoundData soundDataSet;
	SoundData soundDataSet2;
};

