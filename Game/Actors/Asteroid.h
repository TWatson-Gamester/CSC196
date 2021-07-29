#pragma once
#include "Base/Actor.h"
#include "Math/MathUtils.h"

class Asteroid : public gn::Actor {
public:
	Asteroid(const gn::Transform& transform, std::shared_ptr<gn::Shape> shape, float speed, std::string tag) : gn::Actor{ transform, shape }, speed{ speed }, tag{tag} {};
	void Update(float dt) override;

	void OnCollision(Actor* actor) override;

private:
	std::string tag = "";
	float speed = 10;
};