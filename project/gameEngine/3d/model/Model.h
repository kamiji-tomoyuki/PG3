#pragma once
#include <d3d12.h>
#include <wrl.h>

#include <ModelStruct.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class ModelCommon;

// 3Dモデル
class Model
{
private:
	
public:
	// 初期化
	void Initialize(ModelCommon* modelCommon, const std::string& directorypath, const std::string& filename);

	// 更新処理
	void Update();

	// 描画処理
	void Draw();

public:
	ModelData GetModelData() { return modelData_; }

private:
	//Data書き込み
	void VertexResource();
	void MaterialResource();

	// .mtlファイルの読み取り
	static MaterialData LoadMaterialTemplateFile(const std::string& directoryPath, const std::string& filename);
	//.objファイルの読み取り
	static ModelData LoadModelFile(const std::string& directoryPath, const std::string& filename);
	// Animationの解析
	Animation LoadAnimationFile(const std::string& directoryPath, const std::string& filename);
	
	// Node情報の読み取り
	static Node ReadNode(aiNode* node);
	// animationの時刻を取得
	Vector3 CalculateValue(const std::vector<KeyframeVector3>& keyframes, float time);
	Quaternion CalculateValue(const std::vector<KeyframeQuaternion>& keyframes, float time);

private:
	// --- ModelCommon ---
	ModelCommon* modelCommon_;

	// --- Objファイル ---
	ModelData modelData_;
	// アニメーションタイマー
	float animationTime = 0.0f;

	// --- バッファリソース ---
	// VertexResource
	Microsoft::WRL::ComPtr<ID3D12Resource> vertexResource;
	// VertexBufferView
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};
	// VertexResourceにデータを書き込むためのポインタ
	VertexData* vertexData = nullptr;

	// --- マテリアル ---
	// マテリアルリソース
	Microsoft::WRL::ComPtr<ID3D12Resource> materialResource;
	// マテリアルリソースにデータを書き込むためのポインタ
	Material* materialData = nullptr;
	
	// --- アニメーション ---
	Animation animation;
};

