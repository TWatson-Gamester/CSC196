#pragma once
#include "Base/Actor.h"

class Player : public gn::Actor {
public:
	Player(const gn::Transform& transform, gn::Shape* shape, float speed) : gn::Actor{ transform, shape }, speed{ speed } {};
	void Update(float dt) override;

private:
	float speed = 300;
};