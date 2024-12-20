#pragma once
#include <Draw2DStruct.h>
#include <list>
#include <vector>


using namespace std;

// ラインの描画
class Draw2D
{
#pragma region シングルトンインスタンス
private:
	static Draw2D* instance;

	Draw2D() = default;
	~Draw2D() = default;
	Draw2D(const Draw2D&) = delete;
	Draw2D& operator = (const Draw2D&) = delete;

public:
	// シングルトンインスタンスの取得
	static Draw2D* GetInstance();
	// 終了
	void Finalize();
#pragma endregion シングルトンインスタンス

public: 
	
public: // メンバ関数
	// 初期化
	void Initialize(DirectXCommon* dxCommon_);

	// 三角形の描画
	void DrawTriangle(const Vector2& pos1, const Vector2& pos2, const Vector2& pos3, const Vector4& color);

	// 矩形の描画
	void DrawBox(const Vector2& pos, const Vector2& size, const Vector4& color);
	void DrawBox(const Vector2& pos, const Vector2& size, const float angle, const Vector4& color);

	// 線の描画
	void DrawLine(const Vector2& start, const Vector2& end, const Vector4& color);

	// リセット
	void Reset();

public:
	// デバッグ用ビューマトリックスの取得
	const Matrix4x4& GetProjectionMatrix() const { return projectionMatrix_; }

	// プロジェクションマトリックスの設定
	void SetProjectionMatrix(const Matrix4x4& projectionMatrix) { projectionMatrix_ = projectionMatrix; }

private:
	// ルートシグネチャの作成
	void CreateRootSignature(Microsoft::WRL::ComPtr<ID3D12RootSignature>& rootSignature);

	// パイプラインステートの生成
	void CreatePSO(D3D12_PRIMITIVE_TOPOLOGY_TYPE primitiveTopologyType, Microsoft::WRL::ComPtr<ID3D12PipelineState>& pipelineState, Microsoft::WRL::ComPtr<ID3D12RootSignature>& rootSignature);

	// 三角形の頂点データの生成
	void CreateTriangleVertexData(TriangleData* triangleData);

	// 矩形の頂点データの生成
	void CreateBoxVertexData(BoxData* boxData);

	// 線の頂点データの生成
	void CreateLineVertexData(LineData* lineData);

	// 座標変換行列データの生成
	void CreateTransformMatData();

private:
	DirectXCommon* dxCommon_;

	// 三角形データ
	const uint32_t kTrriangleMaxCount = 30096;
	const uint32_t kVertexCountTrriangle = 3;
	uint32_t triangleIndex_ = 0;
	TriangleData* triangleData_;

	// 矩形データ
	const uint32_t kBoxMaxCount = 30096;
	const uint32_t kVertexCountBox = 4;
	const uint32_t kIndexCountBox = 6;
	uint32_t boxIndexIndex_ = 0;
	uint32_t boxVertexIndex_ = 0;
	BoxData* boxData_;

	// 線データ
	const uint32_t kLineMaxCount = 100000;
	const uint32_t kVertexCountLine = 2;
	uint32_t lineIndex_ = 0;
	LineData* lineData_;

	// マトリックス
	Matrix4x4 projectionMatrix_;
	Matrix4x4 viewPortMatrix_;

	// ルートシグネチャ
	Microsoft::WRL::ComPtr<ID3D12RootSignature> triangleRootSignature_;
	Microsoft::WRL::ComPtr<ID3D12RootSignature> lineRootSignature_;
	// パイプラインステート
	Microsoft::WRL::ComPtr<ID3D12PipelineState> trianglePipelineState_;
	Microsoft::WRL::ComPtr<ID3D12PipelineState> linePipelineState_;

	// 座標変換行列バッファ
	Microsoft::WRL::ComPtr<ID3D12Resource> transformationMatrixBuffer_;

	// 座標変換行列データ
	TransformationMatrix2D* transformationMatrixData_;

};