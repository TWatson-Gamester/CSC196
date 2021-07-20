#pragma once

#include "Base/Actor.h"
#include "Math/MathUtils.h"

class Projectile : public gn::Actor {
public:
	Projectile(const gn::Transform& transform, std::shared_ptr<gn::Shape> shape, float speed) : gn::Actor{ transform, shape }, speed{ speed } {};
	void Update(float dt) override;

private:
	float lifetime{ 1 };
	float speed = 300;
};