#include "core.h"
#include "Math/Vector2.h"
#include "Math/Color.h"
#include "Graphics/Shape.h"
#include <iostream>
#include <vector>

using namespace std;

gn::Vector2 position{ 400, 300 };
vector<gn::Vector2> points = { {-25,-25}, {-25,25}, {25,25}, {25,-25}, {-25,-25} };
gn::Shape shape{ points, gn::Color(0,0,1) };
const float speed = 5;
float Time = 0;

bool Update(float dt) {
	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);
	
	Time += dt * 5;

	//int x, y;
	//Core::Input::GetMousePos(x, y);
	//position.x = static_cast<float>(x);
	//position.y = static_cast<float>(y);

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

}

int main() {

	for (int i = 0; i < 10; i++) {
		cout << i << " % 3 = " << i % 3 << endl;
	}

	char name[] = "CSC196";
	Core::Init(name, 800, 600);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	Core::GameLoop();
	Core::Shutdown();
}