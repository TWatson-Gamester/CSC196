#include "core.h"
#include "Math/Vector2.h"
#include "Math/Color.h"
#include "Math/Random.h"
#include "Graphics/Shape.h"
#include "Graphics/ParticleSystem.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

gn::Vector2 position{ 400, 300 };
vector<gn::Vector2> points = { {-25,-25}, {-25,25}, {25,25}, {25,-25}, {-25,-25} };
gn::Shape shape{ points, gn::Color(0,0,1) };
const float speed = 250;
float Time = 0;
gn::ParticleSystem particleSystem;

float deltaTime;
float timer = 0;

bool Update(float dt) {

	deltaTime = dt;
	timer += deltaTime;

	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);
	
	Time += dt * 5;

	if (Core::Input::IsPressed(Core::Input::BUTTON_LEFT)) {
		int x, y;
		Core::Input::GetMousePos(x, y);
		gn::Vector2 psPosition;
		psPosition.x = static_cast<float>(x);
		psPosition.y = static_cast<float>(y);

		vector<gn::Color> colors = { gn::Color::white, gn::Color::red, gn::Color::green, gn::Color::blue };
		particleSystem.Create(psPosition, 250, 2, colors[gn::RandomRangeInt(0,colors.size())], 150);
	}
	particleSystem.Update(dt);

	gn::Vector2 input;
	if (Core::Input::IsPressed('A')) input.x = -1;
	if (Core::Input::IsPressed('D')) input.x = 1;
	if (Core::Input::IsPressed('W')) input.y = -1;
	if (Core::Input::IsPressed('S')) input.y = 1;

	position += input * speed * dt;

	return quit;
}

void Draw(Core::Graphics& graphics) {

		gn::Color color(1, 0, 0);
		color = color * .5f;

		graphics.SetColor(color);

		float scale = 1 + std::sin(Time) * 2;
		shape.Draw(graphics, position);
		particleSystem.Draw(graphics);

		graphics.SetColor(gn::Color::white);
		graphics.DrawString(10, 10, std::to_string(deltaTime).c_str());
		graphics.DrawString(10, 20, std::to_string(timer).c_str());
		graphics.DrawString(10, 30, std::to_string(1 / deltaTime).c_str());

}

int main() {

	srand(1234);
	cout << RAND_MAX << endl;
	for (size_t i = 0; i < 5; i++) {
		int r = rand();
		cout << r << " " << r / static_cast<float>(RAND_MAX) << endl;
	}
	gn::Random();

	char name[] = "CSC196";
	Core::Init(name, 800, 600, 120);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);
	
	particleSystem.Startup();

	Core::GameLoop();
	Core::Shutdown();
	particleSystem.Shutdown();
}