#pragma once
#include "Graphics/ParticleSystem.h"
#include "Audio/AudioSystem.h"

#include "Math/Vector2.h"
#include "Math/Color.h"
#include "Math/Random.h"
#include "Math/MathUtils.h"
#include "Math/Transform.h"

#include "Graphics/Shape.h"

#include "Base/Actor.h"
#include "Base/Scene.h"

#include "Framework/EventSystem.h"

#include "core.h"
#include <vector>
#include <memory>
#include <algorithm>

namespace gn {
	class Engine {
	public:
		void Startup();
		void Shutdown();

		void Update(float dt);

		template<typename T>
		T* Get();

	private:
		std::vector<std::unique_ptr<System>> systems;
	};

	template<typename T>
	inline T* Engine::Get()
	{
		for (auto& system : systems) {
			if ( dynamic_cast<T*>(system.get()) ) return dynamic_cast<T*>(system.get());
			//If it finds the system, then it will return a pointer to it, if not it returns null
		}

		return nullptr;
	}
}