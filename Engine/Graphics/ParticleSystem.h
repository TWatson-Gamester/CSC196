#pragma once
#include "Math/Vector2.h"
#include "Math/Color.h"
#include <vector>
#include "Base/System.h"

namespace gn {

	class ParticleSystem : public System{
	public:
		struct Particle {
			Vector2 position;
			Vector2 prevPosition;
			Vector2 velocity;
			Color color;
			float lifetime;
			bool isActive{ false };

			static bool IsNotActive(Particle p) { return !p.isActive; }

		};

	public:
		void Startup() override;
		void Shutdown() override;

		void Update(float dt) override;
		void Draw(Core::Graphics& graphics);

		void Create(const Vector2& position, size_t count, float lifespan, const Color& color, float speed);

	private:
		std::vector<Particle> particles;
	};

}