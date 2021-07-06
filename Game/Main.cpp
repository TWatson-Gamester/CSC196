#include "core.h"
#include "Math/Vector2.h"
#include "Math/Color.h"
#include "Graphics/Shape.h"
#include "Graphics/ParticleSystem.h"
#include <iostream>
#include <vector>

using namespace std;

gn::Vector2 position{ 400, 300 };
vector<gn::Vector2> points = { {-25,-25}, {-25,25}, {25,25}, {25,-25}, {-25,-25} };
gn::Shape shape{ points, gn::Color(0,0,1) };
const float speed = 5;
float Time = 0;
gn::ParticleSystem particleSystem;

bool Update(float dt) {
	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);
	
	Time += dt * 5;

	if (Core::Input::IsPressed(Core::Input::BUTTON_LEFT)) {
		int x, y;
		Core::Input::GetMousePos(x, y);
		gn::Vector2 psPosition;
		psPosition.x = static_cast<float>(x);
		psPosition.y = static_cast<float>(y);
		particleSystem.Create(psPosition, 50, 2, gn::Color{1, 1, 1}, 150);
	}
	particleSystem.Update(Time);

	gn::Vector2 input;
	if (Core::Input::IsPressed('A')) input.x = -1;
	if (Core::Input::IsPressed('D')) input.x = 1;
	if (Core::Input::IsPressed('W')) input.y = -1;
	if (Core::Input::IsPressed('S')) input.y = 1;

	position += input * speed;

	return quit;
}

void Draw(Core::Graphics& graphics) {

		gn::Color color(0, 0, 1);
		color = color * .5f;

		graphics.SetColor(color);

		float scale = 1 + std::sin(Time) * 2;
		shape.Draw(graphics, position);
		particleSystem.Draw(graphics);

}

int main() {

	

	char name[] = "CSC196";
	Core::Init(name, 800, 600);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);
	
	particleSystem.Startup();

	Core::GameLoop();
	Core::Shutdown();
	particleSystem.Shutdown();
}