#include "Enemy.h"

void Enemy::Update(float dt) {

	Actor::Update(dt);

	transform.position += gn::Vector2::Rotate(gn::Vector2::down, transform.rotation) * speed * dt;
	transform.position.x = gn::Clamp(transform.position.x, 0.0f, 800.0f);
	transform.position.y = gn::Clamp(transform.position.y, 0.0f, 600.0f);
}