#include "Scene.h"
#include "Actor.h"

void gn::Scene::Update(float dt){
	for (auto& actor : actors) {
		actor->Update(dt);
	}
}

void gn::Scene::Draw(Core::Graphics& graphics){
	for (auto& actor : actors) {
		actor->Draw(graphics);
	}
}

void gn::Scene::AddActor(std::unique_ptr<Actor> actor){
	actor.get()->scene = this;
	actors.push_back(std::move(actor));
}
