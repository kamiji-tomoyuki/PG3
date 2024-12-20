#pragma once
#include <DirectXCommon.h>
#include <SrvManager.h>
#include <ParticleStruct.h>
#include <random>
#include <Camera.h>

class ParticleManager
{
#pragma region シングルトンインスタンス
private:
	static ParticleManager* instance;

	ParticleManager() = default;
	~ParticleManager() = default;
	ParticleManager(ParticleManager&) = delete;
	ParticleManager& operator = (ParticleManager&) = delete;

public:
	// シングルトンインスタンスの取得
	static ParticleManager* GetInstance();
	// 終了
	void Finalize();
#pragma endregion シングルトンインスタンス

public:
	// 初期化
	void Initialize(DirectXCommon* dxCommon, SrvManager* srvManager);

	// 更新
	void Update();

	// 描画
	void Draw();

public:
	// ブレンドモード設定
	void SetBlendMode(D3D12_BLEND_DESC& blendDesc, BlendMode blendMode);

	// パーティクルグループ作成
	void CreateParticleGroup(const std::string name, const std::string textureFilePath);

private:
	// ランダムエンジンの初期化
	void InitRandomEngine();

	// ルートシグネチャの作成
	void CreateRootSignature();
	// グラフィックスパイプラインステートの生成
	void CreateGraphicsPipeline();

	// 頂点データ初期化
	void InitVertexData();
	// 頂点リソース生成
	void CreateVertexResources();
	// 頂点バッファビュー生成
	void CreateVBV();
	// 頂点リソースへ書き込み
	void UpdateVertexResources();

private:
	DirectXCommon* dxCommon_;
	SrvManager* srvManager_;

	// --- ルートシグネチャ ---
	Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature;
	// --- グラフィックスパイプライン ---
	Microsoft::WRL::ComPtr<ID3D12PipelineState> graphicsPipelineState;
	
	D3D12_ROOT_SIGNATURE_DESC descriptionRootSignature{};
	D3D12_DESCRIPTOR_RANGE descriptorRangeForInstancing[1] = {};
	
	D3D12_BLEND_DESC blendDesc_{};
	D3D12_DEPTH_STENCIL_DESC depthStencilDesc{};
	D3D12_INPUT_LAYOUT_DESC inputLayoutDesc{};
	D3D12_RASTERIZER_DESC rasterizerDesc{};
	D3D12_GRAPHICS_PIPELINE_STATE_DESC graphicsPipelineStateDesc{};

	D3D12_DESCRIPTOR_RANGE descriptorRange[1] = {};
	D3D12_ROOT_PARAMETER rootParameters[4] = {};
	D3D12_STATIC_SAMPLER_DESC staticSamplers[1] = {};
	D3D12_INPUT_ELEMENT_DESC inputElementDescs[3] = {};
	
	Microsoft::WRL::ComPtr<IDxcBlob> vertexShaderBlob;
	Microsoft::WRL::ComPtr<IDxcBlob> pixelShaderBlob;
	
	VertexData* vertexData = nullptr;

	D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};

	Microsoft::WRL::ComPtr<ID3D12Resource> vertexResource;
	
	ModelData modelData;
	Camera* camera = nullptr;

	// 乱数生成器
	std::random_device seedGenerator;
	std::mt19937 randomEngine;

	// ブレンドモード
	BlendMode currentBlendMode_;

	// パーティクルグループコンテナ
	std::unordered_map<std::string, ParticleGroup> particleGroups_;
	const float kDeltaTime = 1.0f / 60.0f;
};

