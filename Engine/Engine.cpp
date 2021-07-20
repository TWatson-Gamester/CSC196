#include "Engine.h"

namespace gn {
	void Engine::Startup(){
		systems.push_back(std::make_unique<ParticleSystem>());
		systems.push_back(std::make_unique<AudioSystem>());
		systems.push_back(std::make_unique<EventSystem>());

		std::for_each(systems.begin(), systems.end(), [](auto& system) {system->Startup(); });
	}

	void Engine::Shutdown(){
		std::for_each(systems.begin(), systems.end(), [](auto& system) {system->Shutdown(); });
	}

	void Engine::Update(float dt){
		std::for_each(systems.begin(), systems.end(), [dt](auto& system) {system->Update(dt); });
	}
}