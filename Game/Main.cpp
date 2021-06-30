#include "core.h"
#include <iostream>
#include <vector>

using namespace std;

struct Vector2 {
	float x, y;

	Vector2() : x{0}, y{0} {}
	Vector2(float x, float y) : x{x}, y{y} {}
	Vector2(int x, int y) : x{ static_cast<float>(x) }, y{ static_cast<float>(y) } {}

	Vector2 operator + (const Vector2& v) const { return { x + v.x, y + v.y }; }
	Vector2 operator * (float scale) const { return { x * scale, y * scale }; }
	Vector2& operator += (const Vector2& v) { x += v.x; y += v.y; return *this; }
	Vector2& operator *= (float scale) { x *= scale; y *= scale; return *this; }
};

Vector2 position{ 400, 300 };
vector<Vector2> points = { {-50,-50}, {-50,50}, {50,50}, {50,-50}, {-50,-50} };
const float speed = 5;
float Time = 0;

bool Update(float dt) {
	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);
	
	Time += dt * 5;

	//int x, y;
	//Core::Input::GetMousePos(x, y);
	//position.x = static_cast<float>(x);
	//position.y = static_cast<float>(y);

	Vector2 input;
	if (Core::Input::IsPressed('A')) input.x = -1;
	if (Core::Input::IsPressed('D')) input.x = 1;
	if (Core::Input::IsPressed('W')) input.y = -1;
	if (Core::Input::IsPressed('S')) input.y = 1;

	position += input * speed;

	return quit;
}

void Draw(Core::Graphics& graphics) {
	//graphics.SetBackgroundColor(RGB(rand() % 256, rand() % 256, rand() % 256));
	//for (int i = 0; i < 100; i++) {
	//	graphics.SetColor(RGB(rand() % 256, rand() % 256, rand() % 256));
	//	graphics.DrawLine(static_cast<float>(rand() % 801), static_cast<float>(rand() % 601), static_cast<float>(rand() % 801), static_cast<float>(rand() % 601));
	//}
		graphics.SetColor(RGB(255, 0, 0));
		//graphics.DrawLine(0, 0, position.x, position.y);

		float scale = 1 + std::sin(Time) * 2;
		for (size_t i = 0; i < points.size() - 1; i++) {
			Vector2 p1 = ((points[i] * scale) + position) + Vector2{ rand() % 10, rand() % 10 };
			Vector2 p2 = ((points[i + 1] * scale) + position) + Vector2{ rand() % 10, rand() % 10 };
			graphics.DrawLine(p1.x, p1.y, p2.x, p2.y);
			
		}

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