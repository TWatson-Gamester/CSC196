#include "core.h"
#include "Math/Vector2.h"
#include "Math/Color.h"
#include "Math/Random.h"
#include "Math/MathUtils.h"
#include "Graphics/Shape.h"
#include "Graphics/ParticleSystem.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<gn::Vector2> points = { {-25,-25}, {-25,25}, {25,25}, {25,-25}, {-25,-25} };
gn::Shape shape{ points, gn::Color(0,0,1) };
gn::Transform transform{ {400, 300}, 0.0f, 1.0f };

const float speed = 250;
float Time = 0;
gn::ParticleSystem particleSystem;
gn::Vector2 psPosition;
float angle = 0;

float deltaTime;
float timer = 0;

bool Update(float dt) {

	deltaTime = dt;
	timer += deltaTime;

	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);
	
	Time += dt * 5;

	int x, y;
	Core::Input::GetMousePos(x, y);
	psPosition.x = static_cast<float>(x);
	psPosition.y = static_cast<float>(y);

	if (Core::Input::IsPressed(Core::Input::BUTTON_LEFT)) {
		vector<gn::Color> colors = { gn::Color::white, gn::Color::red, gn::Color::green, gn::Color::blue, gn::Color::orange, gn::Color::purple, gn::Color::cyan, gn::Color::yellow };
		particleSystem.Create(psPosition, 250, 2, colors[gn::RandomRangeInt(0,colors.size())], 150);
	}
	particleSystem.Update(dt);

	float thrust = 0;
	if (Core::Input::IsPressed('A')) angle += -5 * dt;
	if (Core::Input::IsPressed('D')) angle += 5 * dt;
	if (Core::Input::IsPressed('W')) thrust = speed;


	//if (Core::Input::IsPressed('S')) input.y = 1;

	transform.position += gn::Vector2::Rotate(gn::Vector2::up, angle) * thrust * dt;
	transform.position.x = gn::Clamp(transform.position.x, 0.0f, 800.0f);
	transform.position.y = gn::Clamp(transform.position.y, 0.0f, 600.0f);

	particleSystem.Create(transform.position, 5, 2, gn::Color::white, 80);

	return quit;
}

void Draw(Core::Graphics& graphics) {

		gn::Color color(1, 0, 0);
		color = color * .5f;

		graphics.SetColor(color);

		float scale = 1 + std::sin(Time) * 2;
		shape.Draw(graphics, transform);
		particleSystem.Draw(graphics);

		color = gn::Lerp(gn::Color::red, gn::Color::yellow, psPosition.x / 800);

		graphics.SetColor(color);
		graphics.DrawString(10, 10, std::to_string(deltaTime).c_str());
		graphics.DrawString(10, 20, std::to_string(timer).c_str());
		graphics.DrawString(10, 30, std::to_string(1 / deltaTime).c_str());

		graphics.DrawString(10, 40, std::to_string(psPosition.Length()).c_str());

}

int main() {
	char name[] = "CSC196";
	Core::Init(name, 800, 600, 120);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);
	
	particleSystem.Startup();

	Core::GameLoop();
	Core::Shutdown();
	particleSystem.Shutdown();
}