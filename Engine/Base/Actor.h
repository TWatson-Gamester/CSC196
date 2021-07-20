#pragma once
#include "Object.h"
#include "core.h"
#include "Math/Transform.h"
#include <memory>

namespace gn {
	class Shape; //Forward declaration, Used for declaring pointers to a class / struct without having to truely declare it
	class Scene;

	class Actor : public Object {
	public:
		Actor(const Transform& transform, std::shared_ptr<Shape> shape) : transform{ transform }, shape{ shape } {};
		virtual void Update(float dt) {}
		virtual void Draw(Core::Graphics& graphics);

		virtual void OnCollision(Actor* actor) {}

	public:
		bool destroy = false;
		Transform transform;
		std::shared_ptr<Shape> shape;
		Scene* scene { nullptr };
	};
}