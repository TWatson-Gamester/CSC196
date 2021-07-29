#include "Game.h"
#include <vector>

void Game::Initialize(){
	engine = std::make_unique<gn::Engine>(); //Makes the new Engine
	engine->Startup();
	scene = std::make_unique<gn::Scene>(); //Makes the Scene
	scene->engine = engine.get();

	engine->Get<gn::AudioSystem>()->AddAudio("explosion", "explosion.wav");
	engine->Get<gn::AudioSystem>()->AddAudio("Player_Shot", "Player_Shot.wav");
	engine->Get<gn::AudioSystem>()->AddAudio("Enemy_Shot", "Enemy_Shot.wav");
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
		UpdateLevelStart(dt);
	}
		break;
	case Game::eState::Game:
		if (scene->GetActors<Enemy>().size() == 0 && scene->GetActors<Asteroid>().size() == 0) {
			state = eState::GameOver;
		}
		if (stateTimer >= 10) {
			scene->AddActor(std::make_unique<Enemy>(gn::Transform{ {gn::RandomRange(0,800),gn::RandomRange(0,600) }, gn::RandomRange(0, 800), 3.0f }, engine->Get<gn::ResourceSystem>()->Get<gn::Shape>("EnemyShape.txt"), 50.0f));
			scene->AddActor(std::make_unique<Asteroid>(gn::Transform{ {gn::RandomRange(0,800),gn::RandomRange(0,600) }, gn::RandomRange(0, 800), 2.0f }, engine->Get<gn::ResourceSystem>()->Get<gn::Shape>("LargeAsteroid.txt"), 10.0f, "Large"));
			scene->AddActor(std::make_unique<Asteroid>(gn::Transform{ {gn::RandomRange(0,800),gn::RandomRange(0,600) }, gn::RandomRange(0, 800), 2.0f }, engine->Get<gn::ResourceSystem>()->Get<gn::Shape>("LargeAsteroid.txt"), 10.0f, "Large"));
			stateTimer = 0;
		}
		break;
	case Game::eState::GameOver:
		scene->RemoveAllActors();
		if (stateTimer >= 5) {
			if (score > HighScore) HighScore = score;
			state = eState::TitleScreen;
			stateTimer = 0;
		}
		break;
	case Game::eState::GameWin:
		scene->RemoveAllActors();
		if (stateTimer >= 5) {
			if (score > HighScore) HighScore = score;
			state = eState::TitleScreen;
			stateTimer = 0;
		}
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
	case Game::eState::GameWin:
		graphics.SetColor(gn::Color::red);
		graphics.DrawString(370, 300 + static_cast<int>(std::sin(stateTimer * 2) * 50), "YOU WIN!");
		break;
	default:
		break;
	}

	graphics.SetColor(gn::Color::white);
	graphics.DrawString(100, 20, std::to_string(HighScore).c_str());
	graphics.DrawString(10, 20, "High Score: ");
	graphics.DrawString(60,40, std::to_string(score).c_str());
	graphics.DrawString(10,40, "Score: ");
	graphics.DrawString(780,20, std::to_string(lives).c_str());
	graphics.DrawString(730,20, "Lives: ");

	scene->Draw(graphics);
	engine->Draw(graphics);
}

void Game::UpdateTitle(float dt){
	if (Core::Input::IsPressed(VK_SPACE)) {
		state = eState::StartGame;
	}
}

void Game::UpdateLevelStart(float dt){

	scene->AddActor(std::make_unique<Player>(gn::Transform{ {400,300},0.0f, 5.0f }, engine->Get<gn::ResourceSystem>()->Get<gn::Shape>("PlayerShape.txt"), 300.0f));
	for (size_t i = 0; i < 2; i++) {
		scene->AddActor(std::make_unique<Enemy>(gn::Transform{ {gn::RandomRange(0,800),gn::RandomRange(0,600) }, gn::RandomRange(0, 800), 3.0f }, engine->Get<gn::ResourceSystem>()->Get<gn::Shape>("EnemyShape.txt"), 50.0f));
	}
	for (size_t i = 0; i < 10; i++) {
		scene->AddActor(std::make_unique<Asteroid>(gn::Transform{ {gn::RandomRange(0,800),gn::RandomRange(0,600) }, gn::RandomRange(0, 800), 2.0f }, engine->Get<gn::ResourceSystem>()->Get<gn::Shape>("LargeAsteroid.txt"), 10.0f, "Large"));
	}
	stateTimer = 0;
	state = eState::Game;
}

void Game::OnAddPoints(const gn::Event& event){
	score += std::get<int>(event.data);
	if (score >= 2000 && lifeCounter == 0) {
		lives++;
		lifeCounter++;
	}
	if (score >= 4000 && lifeCounter == 1) {
		lives++;
		lifeCounter++;
	}
	if (score >= 6000 && lifeCounter == 2) {
		lives++;
		lifeCounter++;
	}
}

void Game::OnPlayerDead(const gn::Event& event){
	lives--;
 	std::cout << std::get<std::string>(event.data) << std::endl;
	if (lives <= 0) {
		state = eState::GameOver;
	}
}
