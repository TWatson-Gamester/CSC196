#pragma once
#include "Base/Actor.h"

class Player : public gn::Actor {
public:
	Player(const gn::Transform& transform, std::shared_ptr<gn::Shape> shape, float speed) : gn::Actor{ transform, shape }, speed{ speed } {};
	void Update(float dt) override;
	void OnCollision(Actor* actor) override;

private:
	float fireTimer{ 0 };
	float fireRate{ .5f };
	float speed = 300;
};