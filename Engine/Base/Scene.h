#pragma once
#include "Object.h"
#include "core.h"
#include <memory>
#include <list>

namespace gn {
	class Actor;

	class Scene : public Object {
	public:
		void Update(float dt);
		void Draw(Core::Graphics& graphics);

		void AddActor(std::unique_ptr<Actor> actor);

		template<typename T>
		T* GetActor();

	private:
		std::list<std::unique_ptr<Actor>> actors;
	};


	template<typename T>
	inline T* Scene::GetActor()
	{
		for (auto& actor : actors) {
			if (dynamic_cast<T*>(actor.get())) {
				return dynamic_cast<T*>(actor.get());
			}
		}
		return nullptr;
	}
}