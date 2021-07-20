#include "Game.h"
#include <vector>

void Game::Initialize(){
	engine = std::make_unique<gn::Engine>(); //Makes the new Engine
	engine->Startup();
	scene = std::make_unique<gn::Scene>(); //Makes the Scene
	scene->engine = engine.get();

	engine->Get<gn::AudioSystem>()->AddAudio("explosion", "explosion.wav");
	stateFunction = &Game::UpdateTitle;

	engine->Get<gn::EventSystem>()->Subscribe("AddPoints", std::bind(&Game::OnAddPoints, this, std::placeholders::_1));
	engine->Get<gn::EventSystem>()->Subscribe("PlayerDead", std::bind(&Game::OnPlayerDead, this, std::placeholders::_1));
}

void Game::Shutdown(){
	scene->RemoveAllActors();
	engine->Shutdown();
}

void Game::Update(float dt){
	stateTimer += dt;
	//(this->*stateFunction)(dt);

	switch (state)
	{
	case Game::eState::TitleScreen:
		if (Core::Input::IsPressed(VK_SPACE)) {
			state = eState::StartGame;
		}
		break;
	case Game::eState::StartGame:
		score = 0;
		lives = 3;
		state = eState::StartLevel;
		break;
	case Game::eState::StartLevel:
	{
		std::shared_ptr<gn::Shape> playerShape = std::make_shared<gn::Shape>();
		playerShape->Load("hourglassShape.txt");

		std::vector<gn::Vector2> points = { {-25,-25}, {-25,25}, {25,25}, {25,-25}, {-25,-25} };
		std::shared_ptr<gn::Shape> enemyShape = std::make_shared<gn::Shape>(points, gn::Color(1, 0, 0));


		scene->AddActor(std::make_unique<Player>(gn::Transform{ {400,300},0.0f, 5.0f }, playerShape, 300.0f));
		for (size_t i = 0; i < 50; i++) {
			scene->AddActor(std::make_unique<Enemy>(gn::Transform{ {gn::RandomRange(0,800),gn::RandomRange(0,600) }, gn::RandomRange(0, 800), 0.5f}, enemyShape, 300.0f));
		}
		state = eState::Game;
	}
		break;
	case Game::eState::Game:
		break;
	case Game::eState::GameOver:
		break;
	default:
		break;
	}

	engine->Update(dt);
	scene->Update(dt);
}

void Game::Draw(Core::Graphics& graphics){
	switch (state)
	{
	case Game::eState::TitleScreen:
		graphics.SetColor(gn::Color::blue);
		graphics.DrawString(340, 300 + static_cast<int>(std::sin(stateTimer * 2) * 50), "This Isn't Asteroids");
		graphics.SetColor(gn::Color::green);
		graphics.DrawString(340, 400, "Press Space to Start");
		break;
	case Game::eState::StartGame:
		break;
	case Game::eState::StartLevel:
		break;
	case Game::eState::Game:
		break;
	case Game::eState::GameOver:
		graphics.SetColor(gn::Color::red);
		graphics.DrawString(370, 300 + static_cast<int>(std::sin(stateTimer * 2) * 50), "GAME OVER");
		break;
	default:
		break;
	}

	graphics.SetColor(gn::Color::white);
	graphics.DrawString(30,20, std::to_string(score).c_str());
	graphics.DrawString(770,20, std::to_string(lives).c_str());

	scene->Draw(graphics);
	engine->Get<gn::ParticleSystem>()->Draw(graphics);
}

void Game::UpdateTitle(float dt){
	if (Core::Input::IsPressed(VK_SPACE)) {
		state = eState::StartGame;
	}
}

void Game::OnAddPoints(const gn::Event& event){
	score += 100;
}

void Game::OnPlayerDead(const gn::Event& event){
	lives--;
	state = eState::GameOver;
}
