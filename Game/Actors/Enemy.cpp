#include "Enemy.h"
#include "Projectile.h"
#include "Engine.h"

void Enemy::Update(float dt) {

	Actor::Update(dt);

	transform.position += gn::Vector2::Rotate(gn::Vector2::down, transform.rotation) * speed * dt;
	transform.position.x = gn::Wrap(transform.position.x, 0.0f, 800.0f);
	transform.position.y = gn::Wrap(transform.position.y, 0.0f, 600.0f);
}

void Enemy::OnCollision(Actor* actor){
	if (dynamic_cast<Projectile*>(actor)) {
		this->destroy = true;
		actor->destroy = true;
		scene->engine->Get<gn::ParticleSystem>()->Create(transform.position, 100, 1, gn::Color::orange, 150);
		scene->engine->Get<gn::ParticleSystem>()->Create(transform.position, 100, 1, gn::Color::red, 150);
		scene->engine->Get<gn::ParticleSystem>()->Create(transform.position, 100, 1, gn::Color::yellow, 150);
		scene->engine->Get<gn::AudioSystem>()->PlayAudio("explosion");

		gn::Event event;
		event.name = "AddPoints";
		scene->engine->Get<gn::EventSystem>()->Notify(event);
	}
}
