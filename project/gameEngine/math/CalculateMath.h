#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include "Matrix4x4.h"
#include "assert.h"
#include <cmath>
#include "Quaternion.h"

// 内積
float Dot(const Vector3& v1, const Vector3& v2);
// 長さ
float Length(const Vector3& v);
float Length(const Vector2& v);
// 距離
float Distance(const Vector3& v1, const Vector3& v2);
// 正規化 v/||v||
Vector3 Normalize(const Vector3& v);
// クロス積
Vector3 Cross(const Vector3& v1, const Vector3& v2);
// 座標変換
Vector3 TransformNormal(const Vector3& v, const Matrix4x4& m);
// Lerp
Vector3 Lerp(const Vector3& start, const Vector3& end, float t);
Quaternion Lerp(const Quaternion& start, const Quaternion& end, float t);

// -----行列-----
// 行列の積
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);
Vector3 Multiply(const Vector3& vec, const Matrix4x4& mat);

// 平行移動行列
Matrix4x4 MakeTranslateMatrix(const Vector3& translate);
// 拡大縮小行列
Matrix4x4 MakeScaleMatrix(const Vector3& scale);
// 回転行列
Matrix4x4 MakeRotateXMatrix(float radian);
Matrix4x4 MakeRotateYMatrix(float radian);
Matrix4x4 MakeRotateZMatrix(float radian);
Matrix4x4 MakeRotateXYZMatrix(Vector3& radian);
// アフィン変換行列
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Quaternion& rotate, const Vector3& translate);

// 逆行列
Matrix4x4 Inverse(const Matrix4x4& m);
// 転置行列
Matrix4x4 Transpose(const Matrix4x4& m);
// 単位行列の作成
Matrix4x4 MakeIdentity4x4();

// 任意軸回転行列
Matrix4x4 MakeRotateAxisAngle(const Vector3& axis, float angle);
// from -> to の回転行列
Matrix4x4 DirectionToDirection(const Vector3& from, const Vector3& to);


// -----座標系-----
// 透視投影行列
Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip);
// 正射影行列
Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip);
// ビューポート変換行列
Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth);
// 座標変換
Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);


// --- Quaternion(仮) ---
// 積
Quaternion Multiply(const Quaternion& Left, const Quaternion& Right);
// 単位Quaternion
Quaternion Identity();
// 共役Quaternion
Quaternion Conjugate(const Quaternion& quaternion);
// Norm
float Norm(const Quaternion& quaternion);
// 正規化Quaternion
Quaternion Normalize(const Quaternion& quaternion);
// 逆Quaternion
Quaternion Inverse(const Quaternion& quaternion);
// 回転
Quaternion MakeRotateAxisAngleQuaternion(const Vector3& axis, float angle);	// 任意軸回転行列
Vector3 RotateVector(const Vector3& vector, const Quaternion& quaternion);	// Quaternionで回転後のベクトル
Matrix4x4 MakeRotateMatrix(const Quaternion& quaternion);					// Quaternion -> 回転行列

// 球面線形補間
Quaternion Slerp(const Quaternion& q0, const Quaternion& q1, float t);
