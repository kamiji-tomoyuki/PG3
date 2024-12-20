#pragma once
#include <Vector3.h>

// ===== 構造体 =====
// 球
struct Sphere 
{
	Vector3 center;//中心点
	float radius;  //半径
};

// 線
struct Line 
{
	Vector3 origin;//始点
	Vector3 diff;//終点への差分ベクトル
};

// AABB
struct AABB 
{
	Vector3 min;//最小点
	Vector3 max;//最大店
};