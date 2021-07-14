#include "Engine.h"
#include "Actors/Player.h"
#include "Actors/Enemy.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<gn::Vector2> points = { {-25,-25}, {-25,25}, {25,25}, {25,-25}, {-25,-25} };

float Time = 0;
gn::Vector2 psPosition;

gn::Engine engine;
gn::Scene scene;

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
		engine.Get<gn::ParticleSystem>()->Create(psPosition, 250, 2, colors[gn::RandomRangeInt(0, colors.size())], 150);
		engine.Get<gn::AudioSystem>()->PlayAudio("explosion");
	}

	scene.GetActor<Player>()->shape->color = gn::Color{ gn::Random(), gn::Random(), gn::Random() };
	scene.GetActor<Enemy>()->shape->color = gn::Color{ gn::Random(), gn::Random(), gn::Random() };

	scene.Update(dt);
	engine.Update(dt);


	//engine.Get<gn::ParticleSystem>()->Create(transform.position, 5, 2, gn::Color::white, 80);

	return quit;
}

void Draw(Core::Graphics& graphics) {

		gn::Color color(1, 0, 0);
		color = color * .5f;

		graphics.SetColor(color);

		float scale = 1 + std::sin(Time) * 2;
		scene.Draw(graphics);
		engine.Get<gn::ParticleSystem>()->Draw(graphics);

		color = gn::Lerp(gn::Color::red, gn::Color::yellow, psPosition.x / 800);

		graphics.SetColor(color);
		graphics.DrawString(10, 10, std::to_string(deltaTime).c_str());
		graphics.DrawString(10, 20, std::to_string(timer).c_str());
		graphics.DrawString(10, 30, std::to_string(1 / deltaTime).c_str());

		graphics.DrawString(10, 40, std::to_string(psPosition.Length()).c_str());

}

void Init() {
	std::shared_ptr<gn::Shape> shape1 = std::make_shared<gn::Shape>( points, gn::Color(0,0,1) );
	std::shared_ptr<gn::Shape> shape2 = std::make_shared<gn::Shape>( points, gn::Color(1,0,0) );

	engine.Get<gn::AudioSystem>()->AddAudio("explosion", "explosion.wav");
	scene.AddActor(std::make_unique<Player>( gn::Transform{{400,300},0.0f, 1.0f}, shape1, 300.0f ));
	for (size_t i = 0; i < 1000; i++) {
		scene.AddActor(std::make_unique<Enemy>( gn::Transform{{400,300},gn::RandomRange(0, 800), 0.5f}, shape2, 300.0f ));
	}

}

int main() {
	char name[] = "CSC196";
	Core::Init(name, 800, 600, 120);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);
	
	engine.Startup();
	Init();

	Core::GameLoop();
	Core::Shutdown();

	engine.Shutdown();
}