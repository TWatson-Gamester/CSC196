#pragma once
#include "Object.h"
#include "core.h"

#include <list>

namespace gn {
	class Actor;

	class Scene : public Object {
	public:
		void Update(float dt);
		void Draw(Core::Graphics& graphics);

		void AddActor(Actor* actor);

	private:
		std::list<Actor*> actors;
	};
}