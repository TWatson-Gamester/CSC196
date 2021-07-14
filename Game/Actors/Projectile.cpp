#include "Projectile.h"

void Projectile::Update(float dt) {

	Actor::Update(dt);

	transform.position += gn::Vector2::Rotate(gn::Vector2::down, transform.rotation) * speed * dt;
	transform.position.x = gn::Wrap(transform.position.x, 0.0f, 800.0f);
	transform.position.y = gn::Wrap(transform.position.y, 0.0f, 600.0f);
}