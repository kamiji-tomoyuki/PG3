#pragma once
#include <Vector4.h>
#include <Vector2.h>
#include <Vector3.h>
#include <string>
#include <vector>
#include <Matrix4x4.h>
#include <list>
#include <wrl.h>
#include <d3d12.h>

// ===== 構造体 =====

// ブレンドモード構造体
enum BlendMode {
	// ブレンド無し
	kBlendModeNone,
	// 通常のブレンド
	kBlendModeNormal,
	// 加算
	kBlendModeAdd,
	// 減算
	kBlendModeSubtract,
	// 乗算
	kBlendModeMultiply,
	// スクリーン
	kBlendModeScreen,

	// 利用してはいけない
	kCount0fBlendMode,
};

// --- 頂点データ ---
struct VertexData {
	Vector4 position;
	Vector2 texcoord;
	Vector3 normal;
};

// --- マテリアルデータ ---
struct MaterialData {
	std::string textureFilePath;
	uint32_t textureIndexSRV = 0;
};

// --- モデルデータ ---
struct ModelData {
	std::vector<VertexData> vertices;
	MaterialData material;
};

// --- Transform ---
struct Transform {
	Vector3 scale;
	Vector3 rotate;
	Vector3 translate;
};

// --- Particle ---
struct Particle {
	Transform transform;
	Vector3 velocity;
	Vector4 color;
	float lifeTime;
	float currentTime;
};

// --- 座標情報 ---
struct ParticleForGPU {
	Matrix4x4 WVP;
	Matrix4x4 World;
	Vector4 color;
};

// --- 全体 ---
struct ParticleGroup {
	MaterialData materialData;										// マテリアルデータ
	std::list<Particle> particles;									// パーティクルリスト
	uint32_t IndexSRV;												// インスタンシングデータ用SRVインデックス
	Microsoft::WRL::ComPtr<ID3D12Resource> instancingResource;		// インスタンシングリソース
	UINT instance;													// インスタンス数
	ParticleForGPU instancingData;									// インスタンシングデータを書き込むためのポインタ
};