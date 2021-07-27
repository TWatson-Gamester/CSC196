#include "Enemy.h"
#include "Projectile.h"
#include "Player.h"
#include "Engine.h"

void Enemy::Update(float dt) {

	Actor::Update(dt);

	if (scene->GetActor<Player>()) {
		gn::Vector2 direction = scene->GetActor<Player>()->transform.position - transform.position;
		gn::Vector2 forward = gn::Vector2::Rotate(gn::Vector2::right, transform.rotation);

		float turnAngle = gn::Vector2::SignedAngle(forward, direction.Normalized());
		transform.rotation = transform.rotation + turnAngle * (3 * dt);

		float angle = gn::Vector2::Angle(direction.Normalized(), forward);

		fireTimer -= dt;
		if (fireTimer <= 0 && angle <= gn::DegToRad(15)) {
			scene->engine->Get<gn::AudioSystem>()->PlayAudio("Enemy_Shot");
			fireTimer = fireRate;
			std::vector<gn::Vector2> points = { {-25,-25}, {-25,25}, {25,25}, {25,-25}, {-25,-25} };
			std::shared_ptr<gn::Shape> shape2 = std::make_shared<gn::Shape>(points, gn::Color(1, 0, 0));

			gn::Transform t = transform;
			t.scale = .5f;
			scene->AddActor(std::make_unique<Projectile>(t, shape2, 600.0f));
		}
	}


	transform.position += gn::Vector2::Rotate(gn::Vector2::right, transform.rotation) * speed * dt;
	transform.position.x = gn::Wrap(transform.position.x, 0.0f, 800.0f);
	transform.position.y = gn::Wrap(transform.position.y, 0.0f, 600.0f);

	transform.Update();
}

void Enemy::OnCollision(Actor* actor){
	if (dynamic_cast<Projectile*>(actor) && actor->tag == "Player") {
		this->destroy = true;
		actor->destroy = true;
		scene->engine->Get<gn::ParticleSystem>()->Create(transform.position, 100, 1, gn::Color::orange, 150);
		scene->engine->Get<gn::ParticleSystem>()->Create(transform.position, 100, 1, gn::Color::red, 150);
		scene->engine->Get<gn::ParticleSystem>()->Create(transform.position, 100, 1, gn::Color::yellow, 150);
		scene->engine->Get<gn::AudioSystem>()->PlayAudio("explosion");

		gn::Event event;
		event.name = "AddPoints";
		event.data = 300;
		scene->engine->Get<gn::EventSystem>()->Notify(event);
	}
}
