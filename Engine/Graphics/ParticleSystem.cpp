#include "ParticleSystem.h"

namespace gn {
	float random() {
		return rand() / static_cast<float>(RAND_MAX);
	}

	float random(float min, float max) {
		return min + (max - min) * random();
	}

	void ParticleSystem::Startup() {
		particles.resize(1000);
	}

	void ParticleSystem::Shutdown() {
		particles.clear();
	}

	void ParticleSystem::Update(float dt) {
		for (Particle& p : particles) {
			if (p.isActive) {
				p.lifetime -= dt;
				p.isActive = p.lifetime > 0;
				p.prevPosition = p.position;
				p.position += (p.velocity * dt);
			}
		}
	}

	void ParticleSystem::Draw(Core::Graphics& graphics) {
		for (const Particle& p : particles) {
			if (p.isActive) {
				graphics.SetColor(p.color);
				graphics.DrawLine(p.position.x, p.position.y, p.prevPosition.x, p.prevPosition.y);
			}
		}
	}

	void ParticleSystem::Create(const Vector2& position, size_t count, float lifespan, const Color& color, float speed){
		for (size_t i = 0; i < count; i++) {
			auto p = std::find_if(particles.begin(), particles.end(), Particle::IsNotActive);
			if (p != particles.end()) {
				p->isActive = true;
				p->lifetime = lifespan;
				p->position = position;
				p->prevPosition = position;
				p->color = color;
				
				p->velocity = Vector2{ random(-1,1), random(-1,1) } * (speed * random());
			}
		}
	}
}