#include "ParticleEmitter.h"


ParticleEmitter::ParticleEmitter(const std::string& name, const Vector3& transform, uint32_t count)
	: emitter_{ name, Vector3{transform}, count,2.0f,0.0f } {}

void ParticleEmitter::Update()
{
}
