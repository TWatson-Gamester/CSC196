#include "Player.h"
#include "Math/MathUtils.h"

void Player::Update(float dt){

	Actor::Update(dt);

	float thrust = 0;
	if (Core::Input::IsPressed('A')) transform.rotation += -5 * dt;
	if (Core::Input::IsPressed('D')) transform.rotation += 5 * dt;
	if (Core::Input::IsPressed('W')) thrust = speed;

	transform.position += gn::Vector2::Rotate(gn::Vector2::up, transform.rotation) * thrust * dt;
	transform.position.x = gn::Clamp(transform.position.x, 0.0f, 800.0f);
	transform.position.y = gn::Clamp(transform.position.y, 0.0f, 600.0f);
}

