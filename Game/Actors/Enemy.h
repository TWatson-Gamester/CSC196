#pragma once
#include "Base/Actor.h"
#include "Math/MathUtils.h"

class Enemy : public gn::Actor {
public:
	Enemy(const gn::Transform& transform, std::shared_ptr<gn::Shape> shape, float speed) : gn::Actor{ transform, shape }, speed{ speed } {};
	void Update(float dt) override;

	void OnCollision(Actor* actor) override;

private:
	float fireTimer{ 0 };
	float fireRate{ 2.0f };
	float speed = 300;
};