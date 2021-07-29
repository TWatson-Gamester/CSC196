#include "Asteroid.h"
#include "Projectile.h"
#include "Player.h"
#include "Engine.h"
#include "Math/Random.h"

void Asteroid::Update(float dt) {

	Actor::Update(dt);

	//if (scene->GetActor<Player>()) {
	//	gn::Vector2 direction = scene->GetActor<Player>()->transform.position - transform.position;
	//	gn::Vector2 forward = gn::Vector2::Rotate(gn::Vector2::right, transform.rotation);

	//	float turnAngle = gn::Vector2::SignedAngle(forward, direction.Normalized());
	//	transform.rotation = transform.rotation + turnAngle * (3 * dt);

	//	float angle = gn::Vector2::Angle(direction.Normalized(), forward);
	//}


	transform.position += gn::Vector2::Rotate(gn::Vector2::right, transform.rotation) * speed * dt;
	transform.position.x = gn::Wrap(transform.position.x, 0.0f, 800.0f);
	transform.position.y = gn::Wrap(transform.position.y, 0.0f, 600.0f);
}

void Asteroid::OnCollision(Actor* actor) {
	if (dynamic_cast<Projectile*>(actor) && actor->tag == "Player") {
		if (tag == "Large") {
			int smallerAsteroids = gn::RandomRangeInt(1, 3);
			for (int i = 0; i < smallerAsteroids; i++) {
				scene->AddActor(std::make_unique<Asteroid>(gn::Transform{ {transform.position.x,transform.position.y }, gn::RandomRange(0, 800), 3.0f }, scene->engine->Get<gn::ResourceSystem>()->Get<gn::Shape>("SmallAsteroid.txt"), 20.0f, "Small"));
			}
		}

		this->destroy = true;
		actor->destroy = true;
		scene->engine->Get<gn::ParticleSystem>()->Create(transform.position, 100, 1, gn::Color::orange, 150);
		scene->engine->Get<gn::ParticleSystem>()->Create(transform.position, 100, 1, gn::Color::red, 150);
		scene->engine->Get<gn::ParticleSystem>()->Create(transform.position, 100, 1, gn::Color::yellow, 150);
		scene->engine->Get<gn::AudioSystem>()->PlayAudio("explosion");

		gn::Event event;
		event.name = "AddPoints";
		if (tag == "Large") {
			event.data = 500;
		}
		else {
			event.data = 100;
		}
		scene->engine->Get<gn::EventSystem>()->Notify(event);
	}
}