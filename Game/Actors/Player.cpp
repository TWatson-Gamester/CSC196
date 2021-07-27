#include "Player.h"
#include "Projectile.h"
#include "Enemy.h"
#include "Engine.h"

void Player::Update(float dt){

	Actor::Update(dt);

	//Movement
	float thrust = 0;
	if (Core::Input::IsPressed('A')) transform.rotation += -5 * dt;
	if (Core::Input::IsPressed('D')) transform.rotation += 5 * dt;
	if (Core::Input::IsPressed('W')) thrust = speed;

	transform.position += gn::Vector2::Rotate(gn::Vector2::right, transform.rotation) * thrust * dt;
	transform.position.x = gn::Clamp(transform.position.x, 0.0f, 800.0f);
	transform.position.y = gn::Clamp(transform.position.y, 0.0f, 600.0f);



	//Fire
	fireTimer -= dt;
	if (fireTimer <= 0 && Core::Input::IsPressed(VK_SPACE)) {
		scene->engine->Get<gn::AudioSystem>()->PlayAudio("Player_Shot");
		fireTimer = fireRate;

		//Need to make custom shape bullets for both player and enimies
		std::vector<gn::Vector2> points = { {-25,-25}, {-25,25}, {25,25}, {25,-25}, {-25,-25} };
		std::shared_ptr<gn::Shape> shape2 = std::make_shared<gn::Shape>(points, gn::Color(1, 0, 0));

		gn::Transform t = transform;
		t.scale = .5f;
		std::unique_ptr<Projectile> projectile = std::make_unique<Projectile>(t, shape2, 600.0f);
		projectile->tag = "Player";
		scene->AddActor(std::move(projectile));
	}

	transform.Update();

}

void Player::OnCollision(Actor* actor) {
	return; // Remove later

	if (dynamic_cast<Enemy*>(actor)) {
		actor->destroy = true;
		scene->engine->Get<gn::ParticleSystem>()->Create(transform.position, 100, 1, gn::Color::orange, 150);
		scene->engine->Get<gn::ParticleSystem>()->Create(transform.position, 100, 1, gn::Color::red, 150);
		scene->engine->Get<gn::ParticleSystem>()->Create(transform.position, 100, 1, gn::Color::yellow, 150);
		scene->engine->Get<gn::AudioSystem>()->PlayAudio("explosion");

		gn::Event event;
		event.name = "PlayerDead";
		event.data = std::string("yep i'm dead");
		scene->engine->Get<gn::EventSystem>()->Notify(event);
	}
}

