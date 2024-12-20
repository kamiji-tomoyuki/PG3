#include "Draw2D.h"
#include "imgui.h"
#include <cassert>

#include "Logger.h"

#include "CalculateMath.h"

Draw2D* Draw2D::instance = nullptr;

Draw2D* Draw2D::GetInstance()
{
	if (instance == nullptr) {
		instance = new Draw2D;
	}
	return instance;
}

void Draw2D::Finalize()
{
	transformationMatrixBuffer_->Release();

	triangleData_->vertexBuffer->Release();

	boxData_->vertexBuffer->Release();
	boxData_->indexBuffer->Release();

	lineData_->vertexBuffer->Release();

	delete instance;
	instance = nullptr;
}

void Draw2D::Initialize(DirectXCommon* dxCommon)
{
	dxCommon_ = dxCommon;

	projectionMatrix_ = MakeOrthographicMatrix(0.0f, 0.0f, float(kClientWidth), float(kClientHeight), 0.0f, 1.0f);
	viewPortMatrix_ = MakeViewportMatrix(0.0f, 0.0f, float(kClientWidth), float(kClientHeight), 0.0f, 1.0f);

	// パイプラインステートの生成
	CreatePSO(D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE, trianglePipelineState_, triangleRootSignature_);
	CreatePSO(D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE, linePipelineState_, lineRootSignature_);

	// 座標変換行列データの生成
	CreateTransformMatData();

	// 三角形の頂点データを生成
	triangleData_ = new TriangleData();
	CreateTriangleVertexData(triangleData_);

	// 矩形の頂点データを生成
	boxData_ = new BoxData();
	CreateBoxVertexData(boxData_);

	// 線の頂点データを生成
	lineData_ = new LineData();
	CreateLineVertexData(lineData_);
}

void Draw2D::DrawTriangle(const Vector2& pos1, const Vector2& pos2, const Vector2& pos3, const Vector4& color)
{

	// 頂点データの設定
	triangleData_->vertexData[triangleIndex_].position = Vector2(pos1.x, pos1.y);
	triangleData_->vertexData[triangleIndex_ + 1].position = Vector2(pos2.x, pos2.y);
	triangleData_->vertexData[triangleIndex_ + 2].position = Vector2(pos3.x, pos3.y);

	// カラーデータの設定
	triangleData_->vertexData[triangleIndex_].color = color;
	triangleData_->vertexData[triangleIndex_ + 1].color = color;
	triangleData_->vertexData[triangleIndex_ + 2].color = color;

	// ルートシグネチャの設定
	dxCommon_->GetCommandList()->SetGraphicsRootSignature(triangleRootSignature_.Get());

	// パイプラインステートの設定
	dxCommon_->GetCommandList()->SetPipelineState(trianglePipelineState_.Get());

	// トポロジの設定
	dxCommon_->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// 頂点バッファビューの設定
	dxCommon_->GetCommandList()->IASetVertexBuffers(0, 1, &triangleData_->vertexBufferView);

	// 座標変換行列の設定
	dxCommon_->GetCommandList()->SetGraphicsRootConstantBufferView(0, transformationMatrixBuffer_->GetGPUVirtualAddress());

	// 描画
	dxCommon_->GetCommandList()->DrawInstanced(kVertexCountTrriangle, 1, static_cast<INT>(triangleIndex_), 0);

	triangleIndex_ += kVertexCountTrriangle + 1;

}

void Draw2D::DrawBox(const Vector2& pos, const Vector2& size, const Vector4& color)
{
	// 頂点データの設定
	boxData_->vertexData[boxVertexIndex_].position = Vector2(pos.x, pos.y);
	boxData_->vertexData[boxVertexIndex_ + 1].position = Vector2(pos.x + size.x, pos.y);
	boxData_->vertexData[boxVertexIndex_ + 2].position = Vector2(pos.x + size.x, pos.y + size.y);
	boxData_->vertexData[boxVertexIndex_ + 3].position = Vector2(pos.x, pos.y + size.y);

	// インデックスデータの設定
	boxData_->indexData[boxIndexIndex_] = 0;
	boxData_->indexData[boxIndexIndex_ + 1] = 1;
	boxData_->indexData[boxIndexIndex_ + 2] = 2;
	boxData_->indexData[boxIndexIndex_ + 3] = 0;
	boxData_->indexData[boxIndexIndex_ + 4] = 2;
	boxData_->indexData[boxIndexIndex_ + 5] = 3;

	// カラーデータの設定
	boxData_->vertexData[boxVertexIndex_].color = color;
	boxData_->vertexData[boxVertexIndex_ + 1].color = color;
	boxData_->vertexData[boxVertexIndex_ + 2].color = color;
	boxData_->vertexData[boxVertexIndex_ + 3].color = color;

	// ルートシグネチャの設定
	dxCommon_->GetCommandList()->SetGraphicsRootSignature(triangleRootSignature_.Get());

	// パイプラインステートの設定
	dxCommon_->GetCommandList()->SetPipelineState(trianglePipelineState_.Get());

	// トポロジの設定
	dxCommon_->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// 頂点バッファビューの設定
	dxCommon_->GetCommandList()->IASetVertexBuffers(0, 1, &boxData_->vertexBufferView);

	// インデックスバッファビューの設定
	dxCommon_->GetCommandList()->IASetIndexBuffer(&boxData_->indexBufferView);

	// 座標変換行列の設定
	dxCommon_->GetCommandList()->SetGraphicsRootConstantBufferView(0, transformationMatrixBuffer_->GetGPUVirtualAddress());

	// 描画
	dxCommon_->GetCommandList()->DrawIndexedInstanced(kIndexCountBox, 1, static_cast<UINT>(boxIndexIndex_), static_cast<INT>(boxVertexIndex_), 0);

	boxIndexIndex_ += kIndexCountBox + 1;
	boxVertexIndex_ += kVertexCountBox + 1;
}

void Draw2D::DrawBox(const Vector2& pos, const Vector2& size, const float angle, const Vector4& color)
{
	// 回転行列の生成
	Matrix4x4 rotationMatrix = MakeRotateZMatrix(angle);

	float left = 0.0f;
	float right = size.x;
	float top = 0.0f;
	float bottom = size.y;

	std::array<Vector2, 4> vertexPos =
	{
		Vector2(left, top),    // 左上
		Vector2(right, top),   // 右上
		Vector2(right, bottom),// 右下
		Vector2(left, bottom), // 左下
	};

	// 回転
	for (auto& vertex : vertexPos)
	{
		Vector3 pos2D = { vertex.x, vertex.y, 0.0f };
		pos2D = Transform(Vector3(pos2D.x, pos2D.y, 0.0f), rotationMatrix);
		vertex = Vector2(pos2D.x, pos2D.y);
	}

	// 頂点データの設定
	boxData_->vertexData[boxVertexIndex_].position = Vector2(pos.x + vertexPos[0].x, pos.y + vertexPos[0].y);
	boxData_->vertexData[boxVertexIndex_ + 1].position = Vector2(pos.x + vertexPos[1].x, pos.y + vertexPos[1].y);
	boxData_->vertexData[boxVertexIndex_ + 2].position = Vector2(pos.x + vertexPos[2].x, pos.y + vertexPos[2].y);
	boxData_->vertexData[boxVertexIndex_ + 3].position = Vector2(pos.x + vertexPos[3].x, pos.y + vertexPos[3].y);

	// インデックスデータの設定
	boxData_->indexData[boxIndexIndex_] = 0;
	boxData_->indexData[boxIndexIndex_ + 1] = 1;
	boxData_->indexData[boxIndexIndex_ + 2] = 2;
	boxData_->indexData[boxIndexIndex_ + 3] = 0;
	boxData_->indexData[boxIndexIndex_ + 4] = 2;
	boxData_->indexData[boxIndexIndex_ + 5] = 3;

	// カラーデータの設定
	boxData_->vertexData[boxVertexIndex_].color = color;
	boxData_->vertexData[boxVertexIndex_ + 1].color = color;
	boxData_->vertexData[boxVertexIndex_ + 2].color = color;
	boxData_->vertexData[boxVertexIndex_ + 3].color = color;

	// ルートシグネチャの設定
	dxCommon_->GetCommandList()->SetGraphicsRootSignature(triangleRootSignature_.Get());

	// パイプラインステートの設定
	dxCommon_->GetCommandList()->SetPipelineState(trianglePipelineState_.Get());

	// トポロジの設定
	dxCommon_->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// 頂点バッファビューの設定
	dxCommon_->GetCommandList()->IASetVertexBuffers(0, 1, &boxData_->vertexBufferView);

	// インデックスバッファビューの設定
	dxCommon_->GetCommandList()->IASetIndexBuffer(&boxData_->indexBufferView);

	// 座標変換行列の設定
	dxCommon_->GetCommandList()->SetGraphicsRootConstantBufferView(0, transformationMatrixBuffer_->GetGPUVirtualAddress());

	// 描画
	dxCommon_->GetCommandList()->DrawIndexedInstanced(kIndexCountBox, 1, static_cast<UINT>(boxIndexIndex_), static_cast<INT>(boxVertexIndex_), 0);

	boxIndexIndex_ += kIndexCountBox + 1;
	boxVertexIndex_ += kVertexCountBox + 1;
}

void Draw2D::DrawLine(const Vector2& start, const Vector2& end, const Vector4& color)
{

	// 頂点データの設定
	lineData_->vertexData[lineIndex_].position = Vector2(start.x, start.y);
	lineData_->vertexData[lineIndex_ + 1].position = Vector2(end.x, end.y);

	// カラーデータの設定
	lineData_->vertexData[lineIndex_].color = color;
	lineData_->vertexData[lineIndex_ + 1].color = color;

	// ルートシグネチャの設定
	dxCommon_->GetCommandList()->SetGraphicsRootSignature(lineRootSignature_.Get());

	// パイプラインステートの設定
	dxCommon_->GetCommandList()->SetPipelineState(linePipelineState_.Get());

	// トポロジの設定
	dxCommon_->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);

	// 頂点バッファビューの設定
	dxCommon_->GetCommandList()->IASetVertexBuffers(0, 1, &lineData_->vertexBufferView);

	// 座標変換行列の設定
	dxCommon_->GetCommandList()->SetGraphicsRootConstantBufferView(0, transformationMatrixBuffer_->GetGPUVirtualAddress());

	// 描画
	dxCommon_->GetCommandList()->DrawInstanced(kVertexCountLine, 1, static_cast<INT>(lineIndex_), 0);

	lineIndex_ += kVertexCountLine + 1;

}

void Draw2D::Reset()
{
	triangleIndex_ = 0;
	boxVertexIndex_ = 0;
	boxIndexIndex_ = 0;
	lineIndex_ = 0;
}

void Draw2D::CreateRootSignature(Microsoft::WRL::ComPtr<ID3D12RootSignature>& rootSignature)
{
	HRESULT hr;

	// rootSignatureの生成
	D3D12_ROOT_SIGNATURE_DESC descriptionRootSignature{};
	descriptionRootSignature.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

	// RootParameterの設定。複数設定できるので配列
	D3D12_ROOT_PARAMETER rootParameters[1] = {};

	rootParameters[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV; // 定数バッファビューを使う
	rootParameters[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX; // 頂点シェーダーで使う
	rootParameters[0].Descriptor.ShaderRegister = 0; // レジスタ番号とバインド

	descriptionRootSignature.pParameters = rootParameters;
	descriptionRootSignature.NumParameters = _countof(rootParameters);

	Microsoft::WRL::ComPtr<ID3DBlob> signatureBlob = nullptr;
	Microsoft::WRL::ComPtr<ID3DBlob> errorBlob = nullptr;

	hr = D3D12SerializeRootSignature(&descriptionRootSignature, D3D_ROOT_SIGNATURE_VERSION_1, &signatureBlob, &errorBlob);
	if (FAILED(hr))
	{
		Logger::Log(reinterpret_cast<char*>(errorBlob->GetBufferPointer()));
		assert(false);
	}

	hr = dxCommon_->GetDevice()->CreateRootSignature(0, signatureBlob->GetBufferPointer(), signatureBlob->GetBufferSize(), IID_PPV_ARGS(rootSignature.GetAddressOf()));
	signatureBlob->GetBufferSize(), IID_PPV_ARGS(rootSignature.GetAddressOf());
	assert(SUCCEEDED(hr));
}

void Draw2D::CreatePSO(D3D12_PRIMITIVE_TOPOLOGY_TYPE primitiveTopologyType, Microsoft::WRL::ComPtr<ID3D12PipelineState>& pipelineState, Microsoft::WRL::ComPtr<ID3D12RootSignature>& rootSignature)
{

	HRESULT hr;

	// RootSignatureの生成
	CreateRootSignature(rootSignature);

	// InputLayout
	D3D12_INPUT_ELEMENT_DESC inputElementDescs[2] = {};
	inputElementDescs[0].SemanticName = "POSITION";
	inputElementDescs[0].SemanticIndex = 0;
	inputElementDescs[0].Format = DXGI_FORMAT_R32G32_FLOAT;
	inputElementDescs[0].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;

	inputElementDescs[1].SemanticName = "COLOR";
	inputElementDescs[1].SemanticIndex = 0;
	inputElementDescs[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	inputElementDescs[1].AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;

	D3D12_INPUT_LAYOUT_DESC inputLayoutDesc{};
	inputLayoutDesc.pInputElementDescs = inputElementDescs;
	inputLayoutDesc.NumElements = _countof(inputElementDescs);

	// BlendState
	D3D12_BLEND_DESC blendDesc{};
	blendDesc.RenderTarget[0].BlendEnable = true;
	blendDesc.RenderTarget[0].SrcBlend = D3D12_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D12_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOp = D3D12_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D12_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D12_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D12_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

	// RasterizerState
	D3D12_RASTERIZER_DESC rasterizerDesc{};
	// 三角形の中を塗りつぶす
	rasterizerDesc.FillMode = D3D12_FILL_MODE_SOLID;
	// 裏面
	rasterizerDesc.CullMode = D3D12_CULL_MODE_NONE;

	// shaderのコンパイル
	Microsoft::WRL::ComPtr<IDxcBlob> vertexShaderBlob = dxCommon_->CompileShader(L"resources/shaders/2D.VS.hlsl", L"vs_6_0");
	assert(vertexShaderBlob != nullptr);

	Microsoft::WRL::ComPtr<IDxcBlob> pixelShaderBlob = dxCommon_->CompileShader(L"resources/shaders/2D.PS.hlsl", L"ps_6_0");
	assert(pixelShaderBlob != nullptr);

	// PSOの生成
	D3D12_GRAPHICS_PIPELINE_STATE_DESC graphicsPipelineStateDesc{};
	graphicsPipelineStateDesc.pRootSignature = triangleRootSignature_.Get();
	graphicsPipelineStateDesc.InputLayout = inputLayoutDesc;
	graphicsPipelineStateDesc.VS = { vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize() };
	graphicsPipelineStateDesc.PS = { pixelShaderBlob->GetBufferPointer(), pixelShaderBlob->GetBufferSize() };
	graphicsPipelineStateDesc.BlendState = blendDesc;
	graphicsPipelineStateDesc.RasterizerState = rasterizerDesc;
	// 書き込むRTVの情報
	graphicsPipelineStateDesc.NumRenderTargets = 1;
	graphicsPipelineStateDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	// 利用するトポロジ（形状）のタイプ。三角形
	graphicsPipelineStateDesc.PrimitiveTopologyType = primitiveTopologyType;
	// どのように画面に色を打ち込むかの設定
	graphicsPipelineStateDesc.SampleDesc.Count = 1;
	graphicsPipelineStateDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;

	// 実際に生成
	hr = dxCommon_->GetDevice()->CreateGraphicsPipelineState(&graphicsPipelineStateDesc, IID_PPV_ARGS(&pipelineState));
	assert(SUCCEEDED(hr));
}

void Draw2D::CreateTriangleVertexData(TriangleData* triangleData)
{
	UINT vertexBufferSize = sizeof(VertexData2D) * kVertexCountTrriangle * kTrriangleMaxCount;

	// 頂点リソースを生成
	triangleData->vertexBuffer = dxCommon_->CreateBufferResource(vertexBufferSize);
	//m_dx12_->CreateBufferResource(triangleData->vertexBuffer, vertexBufferSize);

	// 頂点バッファビューを作成する
	triangleData->vertexBufferView.BufferLocation = triangleData->vertexBuffer->GetGPUVirtualAddress();
	triangleData->vertexBufferView.SizeInBytes = vertexBufferSize;
	triangleData->vertexBufferView.StrideInBytes = sizeof(VertexData2D);

	// 頂点リソースをマップ
	triangleData->vertexBuffer->Map(0, nullptr, reinterpret_cast<void**>(&triangleData->vertexData));

}

void Draw2D::CreateBoxVertexData(BoxData* boxData)
{
	UINT vertexBufferSize = sizeof(VertexData2D) * kVertexCountBox * kBoxMaxCount;
	UINT indexBufferSize = sizeof(uint32_t) * kIndexCountBox * kBoxMaxCount;

	// 頂点リソースを生成
	boxData->vertexBuffer = dxCommon_->CreateBufferResource(vertexBufferSize);

	// インデックスリソースを生成
	boxData->indexBuffer = dxCommon_->CreateBufferResource(indexBufferSize);

	// 頂点バッファビューを作成する
	boxData->vertexBufferView.BufferLocation = boxData->vertexBuffer->GetGPUVirtualAddress();
	boxData->vertexBufferView.SizeInBytes = vertexBufferSize;
	boxData->vertexBufferView.StrideInBytes = sizeof(VertexData2D);

	// インデックスバッファビューを作成する
	boxData->indexBufferView.BufferLocation = boxData->indexBuffer->GetGPUVirtualAddress();
	boxData->indexBufferView.SizeInBytes = indexBufferSize;
	boxData->indexBufferView.Format = DXGI_FORMAT_R32_UINT;

	// 頂点リソースをマップ
	boxData->vertexBuffer->Map(0, nullptr, reinterpret_cast<void**>(&boxData->vertexData));

	// インデックスリソースをマップ
	boxData->indexBuffer->Map(0, nullptr, reinterpret_cast<void**>(&boxData->indexData));
}

void Draw2D::CreateLineVertexData(LineData* lineData)
{
	UINT vertexBufferSize = sizeof(VertexData2D) * kVertexCountLine * kLineMaxCount;

	// 頂点リソースを生成
	lineData->vertexBuffer = dxCommon_->CreateBufferResource(vertexBufferSize);
	//m_dx12_->CreateBufferResource(lineData->vertexBuffer, vertexBufferSize);

	// 頂点バッファビューを作成する
	lineData->vertexBufferView.BufferLocation = lineData->vertexBuffer->GetGPUVirtualAddress();
	lineData->vertexBufferView.SizeInBytes = vertexBufferSize;
	lineData->vertexBufferView.StrideInBytes = sizeof(VertexData2D);

	// 頂点リソースをマップ
	lineData->vertexBuffer->Map(0, nullptr, reinterpret_cast<void**>(&lineData->vertexData));
}

void Draw2D::CreateTransformMatData()
{
	// 座標変換行列リソースを生成
	transformationMatrixBuffer_ = dxCommon_->CreateBufferResource(sizeof(TransformationMatrix2D));

	// 座標変換行列リソースをマップ
	transformationMatrixBuffer_->Map(0, nullptr, reinterpret_cast<void**>(&transformationMatrixData_));

	transformationMatrixData_->WVP = projectionMatrix_;
}




