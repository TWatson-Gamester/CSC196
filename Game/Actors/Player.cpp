#include "Player.h"
#include "Projectile.h"
#include "Engine.h"

void Player::Update(float dt){

	Actor::Update(dt);

	//Movement
	float thrust = 0;
	if (Core::Input::IsPressed('A')) transform.rotation += -5 * dt;
	if (Core::Input::IsPressed('D')) transform.rotation += 5 * dt;
	if (Core::Input::IsPressed('W')) thrust = speed;

	transform.position += gn::Vector2::Rotate(gn::Vector2::up, transform.rotation) * thrust * dt;
	transform.position.x = gn::Clamp(transform.position.x, 0.0f, 800.0f);
	transform.position.y = gn::Clamp(transform.position.y, 0.0f, 600.0f);

	//Fire
	if (Core::Input::IsPressed(VK_SPACE)) {
		std::vector<gn::Vector2> points = { {-25,-25}, {-25,25}, {25,25}, {25,-25}, {-25,-25} };
		std::shared_ptr<gn::Shape> shape2 = std::make_shared<gn::Shape>(points, gn::Color(1, 0, 0));

		gn::Transform t = transform;
		t.scale = .5f;
		scene->AddActor(std::make_unique<Projectile>( t, shape2, 600.0f ));
	}
}

