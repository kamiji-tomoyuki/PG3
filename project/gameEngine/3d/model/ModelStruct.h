#pragma once
#include <map>
#include <string>
#include <vector>

#include <Vector2.h>
#include <Vector3.h>
#include <Vector4.h>
#include <Matrix4x4.h>
#include <Quaternion.h>

// ===== 構造体 =====

// --- 頂点データ ---
struct VertexData {
	Vector4 position;
	Vector2 texcoord;
	Vector3 normal;
};

// --- 色データ ---
struct Color {
	float r, g, b;
};

// --- マテリアル ---
struct Material {
	Vector4 color;
	int32_t enableLighting;
	float padding[3];
	Matrix4x4 uvTransform;
};

// --- マテリアルデータ ---
struct MaterialData {
	std::string name;
	float Ns;
	Color Ka; // 環境光色
	Color Kd; // 拡散反射色
	Color Ks; // 鏡面反射光
	float Ni;
	float d;
	uint32_t illum;
	std::string textureFilePath;
	uint32_t textureIndex = 0;
};

// --- 座標変換 ---
struct TransformationMatrix {
	Matrix4x4 WVP;
	Matrix4x4 World;
};

// --- 平行光源 ---
struct DirectionalLight {
	Vector4 color;     // ライトの色
	Vector3 direction; // ライトの向き
	float intensity;   // 輝度
};

// --- Node情報 ---
struct Node {
	Matrix4x4 localMatrix;
	std::string name;
	std::vector<Node> children;
};

// --- モデルデータ ---
struct ModelData {
	std::vector<VertexData> vertices;
	MaterialData material;
	Node rootNode;
	bool isAnimation;
};

// --- キーフレーム ---
template <typename tValue>
struct Keyframe {
	float time;		// キーフレームの時刻
	tValue value;	// キーフレームの値
};

using KeyframeVector3 = Keyframe<Vector3>;
using KeyframeQuaternion = Keyframe<Quaternion>;

// --- Nodeのアニメーション ---
template <typename tValue>
struct AnimationCurve {
	std::vector<Keyframe<tValue>> keyframes;
};

struct NodeAnimation
{
	std::vector<KeyframeVector3> translate;
	std::vector<KeyframeQuaternion> rotate;
	std::vector<KeyframeVector3> scale;
};

// --- アニメーション ---
struct Animation
{
	float duration;	//アニメーション全体の尺
	// NodeAnimationの集合
	std::map<std::string, NodeAnimation> nodeAnimations;
};
