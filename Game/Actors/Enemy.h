#pragma once
#include "Base/Actor.h"
#include "Math/MathUtils.h"

class Enemy : public gn::Actor {
public:
	Enemy(const gn::Transform& transform, gn::Shape* shape, float speed) : gn::Actor{ transform, shape }, speed{ speed } {};
	void Update(float dt) override;

private:
	float speed = 300;
};