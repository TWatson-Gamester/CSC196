#include "Player.h"
#include "Projectile.h"
#include "Enemy.h"
#include "Asteroid.h"
#include "Engine.h"

Player::Player(const gn::Transform& transform, std::shared_ptr<gn::Shape> shape, float speed) : gn::Actor{ transform,shape }, speed{ speed } {
	
}

void Player::Update(float dt){

	Actor::Update(dt);

	//Movement
	float thrust = 0;
	if (Core::Input::IsPressed('A')) transform.rotation += -5 * dt;
	if (Core::Input::IsPressed('D')) transform.rotation += 5 * dt;
	if (Core::Input::IsPressed('W')) thrust = speed;

	gn::Vector2 acceleration = gn::Vector2::Rotate(gn::Vector2::right, transform.rotation) * thrust;
	gn::Vector2 gravity = (gn::Vector2{ 400,300 } - transform.position).Normalized() * 100;
	acceleration += gravity;
	velocity += acceleration * dt;
	velocity *= 0.99f;

	transform.position += velocity * dt;
	transform.position.x = gn::Clamp(transform.position.x, 0.0f, 800.0f);
	transform.position.y = gn::Clamp(transform.position.y, 0.0f, 600.0f);



	//Fire
	fireTimer -= dt;
	if (fireTimer <= 0 && Core::Input::IsPressed(VK_SPACE)) {
		scene->engine->Get<gn::AudioSystem>()->PlayAudio("Player_Shot");
		fireTimer = fireRate;

		//Need to make custom shape bullets for both player and enimies
		gn::Transform t = children[0]->transform;
		t.scale = .5f;
		std::unique_ptr<Projectile> projectile = std::make_unique<Projectile>(t, scene->engine->Get<gn::ResourceSystem>()->Get<gn::Shape>("ProjectileShape.txt"), 600.0f);
		projectile->tag = "Player";
		scene->AddActor(std::move(projectile));
	}
}

void Player::OnCollision(Actor* actor) {

	if (dynamic_cast<Enemy*>(actor) || dynamic_cast<Asteroid*>(actor)) {
		actor->destroy = true;
		scene->engine->Get<gn::ParticleSystem>()->Create(transform.position, 100, 1, gn::Color::orange, 150);
		scene->engine->Get<gn::ParticleSystem>()->Create(transform.position, 100, 1, gn::Color::red, 150);
		scene->engine->Get<gn::ParticleSystem>()->Create(transform.position, 100, 1, gn::Color::yellow, 150);
		scene->engine->Get<gn::AudioSystem>()->PlayAudio("explosion");

		gn::Event event;
		event.name = "PlayerDead";
		event.data = std::string("I got Hit");
		scene->engine->Get<gn::EventSystem>()->Notify(event);
	}
	else if (dynamic_cast<Projectile*>(actor) && actor->tag == "Enemy") {
		actor->destroy = true;
		scene->engine->Get<gn::ParticleSystem>()->Create(transform.position, 100, 1, gn::Color::orange, 150);
		scene->engine->Get<gn::ParticleSystem>()->Create(transform.position, 100, 1, gn::Color::red, 150);
		scene->engine->Get<gn::ParticleSystem>()->Create(transform.position, 100, 1, gn::Color::yellow, 150);
		scene->engine->Get<gn::AudioSystem>()->PlayAudio("explosion");

		gn::Event event;
		event.name = "PlayerDead";
		event.data = std::string("I got Hit");
		scene->engine->Get<gn::EventSystem>()->Notify(event);
	}
}

void Player::Initialize(){
	std::unique_ptr locator = std::make_unique<Actor>();
	locator->transform.localPosition = gn::Vector2{ 8,0 };
	AddChild(std::move(locator));

	locator = std::make_unique<Actor>();
	locator->transform.localPosition = gn::Vector2{ 0,5 };
	AddChild(std::move(locator));
}

