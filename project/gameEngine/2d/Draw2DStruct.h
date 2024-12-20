#pragma once
#include "DirectXCommon.h"

#include <Vector2.h>
#include <Vector3.h>
#include <Vector4.h>
#include <Matrix4x4.h>

// ===== 構造体 =====
struct VertexData2D
{
	Vector2 position;
	Vector4 color;
};

// 座標変換行列
struct TransformationMatrix2D
{
	Matrix4x4 WVP;
};

// 三角形
struct TriangleData
{
	VertexData2D* vertexData;
	// 頂点バッファ
	Microsoft::WRL::ComPtr<ID3D12Resource> vertexBuffer;
	// 頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView;
};

// 矩形
struct BoxData
{
	VertexData2D* vertexData;
	uint32_t* indexData;
	// 頂点バッファ
	Microsoft::WRL::ComPtr<ID3D12Resource> vertexBuffer;
	// インデックスバッファ
	Microsoft::WRL::ComPtr<ID3D12Resource> indexBuffer;
	// 頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView;
	// インデックスバッファビュー
	D3D12_INDEX_BUFFER_VIEW indexBufferView;
};

// 線分
struct LineData
{
	VertexData2D* vertexData;
	// 頂点バッファ
	Microsoft::WRL::ComPtr<ID3D12Resource> vertexBuffer;
	// 頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView;
};

// 球
struct Sphere {
	Vector3 center;
	float radius;
};
