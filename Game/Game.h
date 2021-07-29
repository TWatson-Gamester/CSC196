#pragma once
#include "core.h"
#include "Engine.h"
#include "Actors/Player.h"
#include "Actors/Projectile.h"
#include "Actors/Enemy.h"
#include "Actors/Asteroid.h"

#include <memory>

class Game {

public:
	enum class eState {
		TitleScreen,
		StartGame,
		StartLevel,
		Game,
		GameOver,
		GameWin
	};

public:
	void Initialize();
	void Shutdown();

	void Update(float dt);
	void Draw(Core::Graphics& graphics);

private:
	void UpdateTitle(float dt);
	void UpdateLevelStart(float dt);
	void OnAddPoints(const gn::Event& event);
	void OnPlayerDead(const gn::Event& event);

public:
	std::unique_ptr<gn::Engine> engine;
	std::unique_ptr<gn::Scene> scene;
	
	void (Game::*stateFunction)(float) = nullptr;

private:
	eState state = eState::TitleScreen;
	float stateTimer = 0.0f;
	size_t HighScore = 0;
	size_t lifeCounter = 0;
	size_t score = 0;
	size_t lives = 0;
	bool waitTimer = true;
};