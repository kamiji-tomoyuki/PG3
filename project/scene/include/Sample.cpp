#include "Sample.h"
#include <ModelManager.h>

void Sample::Initialize()
{
	// --- スプライト ---
	// スプライト名の指定 (「 Resources / images 」は省略 )
	std::string textureFile = "monsterBall.png";
	// 生成・初期化
	sprite = std::make_unique<Sprite>();
	sprite->Initialize(textureFile, { 0,0 }, { 1,1,1,1 }, { 0,0 });	// ( テクスチャ変数, 位置, 色, アンカーポイント );
	sprite->SetSize({ 200.0f,200.0f });

	// --- 3Dオブジェクト ---
	// オブジェクト読み込み (「 Resources / models 」は省略 )
	ModelManager::GetInstance()->LoadModel("animation/AnimatedCube.gltf");
	// 生成・初期化
	object3d = std::make_unique<Object3d>();
	object3d->Initialize("AnimatedCube.gltf");	// ( .obj or .gltf のみ );
}

void Sample::Update()
{
	// Sprite更新処理
	UpdateSprite();

	// Object3d更新処理
	UpdateObj();
}

void Sample::Draw()
{
	// --- スプライト ---
	sprite->Draw();

	// --- 3Dオブジェクト ---
	object3d->Draw();
}

void Sample::UpdateSprite()
{
	// --- スプライト ---
	// ( ↓ 変更可能ステータス ↓ )
	// 座標
	Vector2 position2D = sprite->GetPosition();
	sprite->SetPosition(position2D);
	// 回転
	float rotation2D = sprite->GetRotate();
	sprite->SetRotate(rotation2D);
	// スケール
	Vector2 size2D = { 200.0f,200.0f };
	sprite->SetSize(size2D);
	// 色
	Vector4 color = sprite->GetColor();
	sprite->SetColor(color);
}

void Sample::UpdateObj()
{
	// --- 3Dオブジェクト ---
	// // ( ↓ 変更可能ステータス ↓ )
	// 座標
	Vector3 position3D = object3d->GetPosition();
	object3d->SetPosition(position3D);
	// 回転
	Vector3 rotation3D = object3d->GetRotate();
	object3d->SetRotate(rotation3D);
	// スケール
	Vector3 size3D = object3d->GetSize();
	object3d->SetSize(size3D);
}
