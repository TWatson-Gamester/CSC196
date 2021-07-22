#include "Game.h"
#include <variant>

using namespace std;

Game game;


bool Update(float dt) {

	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);
	game.Update(dt);

	//int x, y;
	//Core::Input::GetMousePos(x, y);
	//psPosition.x = static_cast<float>(x);
	//psPosition.y = static_cast<float>(y);

	//
	//if (Core::Input::IsPressed(Core::Input::BUTTON_LEFT)) {
	//	vector<gn::Color> colors = { gn::Color::white, gn::Color::red, gn::Color::green, gn::Color::blue, gn::Color::orange, gn::Color::purple, gn::Color::cyan, gn::Color::yellow };
	//	engine.Get<gn::ParticleSystem>()->Create(psPosition, 250, 2, colors[gn::RandomRangeInt(0, colors.size())], 150);
	//	engine.Get<gn::AudioSystem>()->PlayAudio("explosion");
	//}

	return quit;
}

void Draw(Core::Graphics& graphics) {
	game.Draw(graphics);
}

void Init() {
	game.Initialize();
}

int inc(int i) { return ++i; }
int dec(int i) { return --i; }

union Data {
	int i;
	char str[5];
	bool b;
};

int main() {

	Data data = { 0 };
	data.b = true;
	data.i = 534;
	data.str[0] = '#';
	cout << data.i << endl;
	cout << data.b << endl;
	cout << data.str << endl;

	std::variant<int, std::string, float, bool> var;
	var = 20;
	var = true;

	//cout << "Var int: " << std::get<int>(var) << endl;
	cout << "Var bool: " << std::get<bool>(var) << endl;
	cout << "Var bool: " << std::get<3>(var) << endl;

	//int (*operation)(int);

	//operation = &inc;

	//cout << operation(5) << endl;

	//operation = &dec;
	//
	//cout << operation(5) << endl;

	//system("pause");

	char name[] = "CSC196";
	Core::Init(name, 800, 600, 120);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);
	
	game.Initialize();

	Core::GameLoop();
	Core::Shutdown();

	game.Shutdown();
}