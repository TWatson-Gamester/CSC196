#pragma once
#include "Object.h"
#include "core.h"
#include "Math/Transform.h"

namespace gn {
	class Shape; //Forward declaration, Used for declaring pointers to a class / struct without having to truely declare it

	class Actor : public Object {
	public:
		Actor(const Transform& transform, Shape* shape) : transform{ transform }, shape{ shape } {};
		virtual void Update(float dt);
		virtual void Draw(Core::Graphics& graphics);

	public:
		Transform transform;
		Shape* shape;
	};
}