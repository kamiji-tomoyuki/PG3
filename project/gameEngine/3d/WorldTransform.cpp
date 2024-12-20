#include "WorldTransform.h"
#include <cassert>

void WorldTransform::Initialize() {
    // 行列を単位行列に初期化
    matWorld_ = MakeIdentity4x4();

    // 定数バッファ生成
    CreateConstBuffer();
    // 定数バッファをマッピング
    Map();
}

void WorldTransform::CreateConstBuffer() {
    HRESULT result;

    // 定数バッファ用ヒーププロパティ
    D3D12_HEAP_PROPERTIES heapProps = {};
    heapProps.Type = D3D12_HEAP_TYPE_UPLOAD;
    heapProps.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
    heapProps.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
    heapProps.CreationNodeMask = 1;
    heapProps.VisibleNodeMask = 1;

    // リソースディスクリプタ
    D3D12_RESOURCE_DESC resourceDesc = {};
    resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
    resourceDesc.Alignment = 0;
    resourceDesc.Width = (sizeof(ConstBufferDataWorldTransform) + 255) & ~255; // 256バイトアラインメント
    resourceDesc.Height = 1;
    resourceDesc.DepthOrArraySize = 1;
    resourceDesc.MipLevels = 1;
    resourceDesc.Format = DXGI_FORMAT_UNKNOWN;
    resourceDesc.SampleDesc.Count = 1;
    resourceDesc.SampleDesc.Quality = 0;
    resourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
    resourceDesc.Flags = D3D12_RESOURCE_FLAG_NONE;

    // 定数バッファの生成
    result = dxCommon_->GetDevice()->CreateCommittedResource(
        &heapProps,
        D3D12_HEAP_FLAG_NONE,
        &resourceDesc,
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(&constBuffer_)
    );
    assert(SUCCEEDED(result) && "Failed to create constant buffer.");
}

void WorldTransform::Map() {
    // 定数バッファのマッピング
    HRESULT result = constBuffer_->Map(0, nullptr, reinterpret_cast<void**>(&constMap));
    assert(SUCCEEDED(result) && "Failed to map constant buffer.");
}

void WorldTransform::TransferMatrix() {
    assert(constMap && "Constant buffer is not mapped.");
    constMap->matWorld = matWorld_;
}

void WorldTransform::UpdateMatrix() {
    // スケール、回転、移動行列を計算
    Matrix4x4 scaleMatrix = MakeScaleMatrix(scale_);
    Matrix4x4 rotationMatrix = MakeRotateXYZMatrix(rotation_);
    Matrix4x4 translationMatrix = MakeTranslateMatrix(translation_);

    // ワールド行列を結合
    matWorld_ = scaleMatrix * rotationMatrix * translationMatrix;

    // 親が存在する場合は親の行列も適用
    if (parent_) {
        matWorld_ = parent_->matWorld_ * matWorld_;
    }
}