#pragma once
#include <CollisionStruct.h>
#include <Matrix4x4.h>


class Draw3D
{
#pragma region シングルトンインスタンス
private:
	static Draw3D* instance;

	Draw3D() = default;
	~Draw3D() = default;
	Draw3D(const Draw3D&) = delete;
	Draw3D& operator = (const Draw3D&) = delete;

public:
	// シングルトンインスタンスの取得
	static Draw3D* GetInstance();
	// 終了
	void Finalize();
#pragma endregion シングルトンインスタンス

public: // メンバ関数
	// 初期化
	void Initialize();

	void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);


};

