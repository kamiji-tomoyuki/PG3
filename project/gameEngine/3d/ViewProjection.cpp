#include "ViewProjection.h"
#include <DirectXMath.h>
#include <stdexcept>

using namespace DirectX;

void ViewProjection::Initialize() {
    // ビュー行列と射影行列を初期化
    UpdateViewMatrix();
    UpdateProjectionMatrix();
    CreateConstBuffer();
    Map();
}

void ViewProjection::CreateConstBuffer() {
    // 定数バッファのリソースを作成
    D3D12_HEAP_PROPERTIES heapProps = {};
    heapProps.Type = D3D12_HEAP_TYPE_UPLOAD;
    heapProps.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
    heapProps.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
    heapProps.CreationNodeMask = 1;
    heapProps.VisibleNodeMask = 1;

    D3D12_RESOURCE_DESC resourceDesc = {};
    resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
    resourceDesc.Alignment = 0;
    resourceDesc.Width = (sizeof(ConstBufferDataViewProjection) + 255) & ~255; // 256バイトアラインメント
    resourceDesc.Height = 1;
    resourceDesc.DepthOrArraySize = 1;
    resourceDesc.MipLevels = 1;
    resourceDesc.Format = DXGI_FORMAT_UNKNOWN;
    resourceDesc.SampleDesc.Count = 1;
    resourceDesc.SampleDesc.Quality = 0;
    resourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
    resourceDesc.Flags = D3D12_RESOURCE_FLAG_NONE;

    HRESULT hr = dxCommon_->GetDevice()->CreateCommittedResource(
        &heapProps,
        D3D12_HEAP_FLAG_NONE,
        &resourceDesc,
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(&constBuffer_)
    );

    if (FAILED(hr)) {
        throw std::runtime_error("Failed to create constant buffer.");
    }
}

void ViewProjection::Map() {
    // 定数バッファをマップ
    D3D12_RANGE readRange = {}; // 読み取り範囲なし
    HRESULT hr = constBuffer_->Map(0, &readRange, reinterpret_cast<void**>(&constMap));
    if (FAILED(hr)) {
        throw std::runtime_error("Failed to map constant buffer.");
    }
}

void ViewProjection::UpdateMatrix() {
    // 行列を更新し、定数バッファに転送
    UpdateViewMatrix();
    UpdateProjectionMatrix();
    TransferMatrix();
}

void ViewProjection::UpdateViewMatrix() {
    // 回転行列
    XMMATRIX rotX = XMMatrixRotationX(rotation_.x);
    XMMATRIX rotY = XMMatrixRotationY(rotation_.y);
    XMMATRIX rotZ = XMMatrixRotationZ(rotation_.z);

    // 平行移動行列
    XMMATRIX trans = XMMatrixTranslation(translation_.x, translation_.y, translation_.z);

    // ビュー行列を作成
    XMMATRIX view = XMMatrixInverse(nullptr, rotX * rotY * rotZ * trans);
    XMStoreMatrix4x4(matView, view);
}

void ViewProjection::UpdateProjectionMatrix() {
    // 射影行列を作成
    XMMATRIX proj = XMMatrixPerspectiveFovLH(fovAngleY, aspectRatio, nearZ, farZ);
    XMStoreMatrix4x4(matProjection, proj);
}

void ViewProjection::XMStoreMatrix4x4(Matrix4x4& dest, const DirectX::XMMATRIX& src)
{
    // src は 4x4 の行列で、dest の要素にコピーする
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            dest.m[i][j] = src.r[i].m128_f32[j];
        }
    }
}

void ViewProjection::TransferMatrix() {
    // 定数バッファへデータ転送
    if (constMap) {
        constMap->view = matView;
        constMap->projection = matProjection;
        constMap->cameraPos = translation_; // カメラ位置の更新
    }
}