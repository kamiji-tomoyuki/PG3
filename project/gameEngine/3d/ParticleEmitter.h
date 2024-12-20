#pragma once
#include "ParticleManager.h"



class ParticleEmitter
{
public:
	// コンストラクタ
	ParticleEmitter(const std::string& name, const Vector3& transform, uint32_t count);

	// 更新
	void Update();

public:

	void SetPosition(Vector3& position) { emitter_.transform = position; };
	void SetCount(uint32_t& setcount) { emitter_.count = setcount; };

private:
	// エミッター
	void Emit();

private:
	struct Emitter {
		Transform transform;
		uint32_t count;			//発生数
		float frequency;		//発生頻度
		float frequencyTime;	//頻度用時刻
	};
	Emitter emitter_{};

	float deltaTime_ = 1.0f / 60.0f;
};

