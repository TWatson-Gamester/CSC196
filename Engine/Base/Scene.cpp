#include "Scene.h"
#include "Actor.h"

void gn::Scene::Update(float dt){
	for (Actor* actor : actors) {
		actor->Update(dt);
	}
}

void gn::Scene::Draw(Core::Graphics& graphics){
	for (Actor* actor : actors) {
		actor->Draw(graphics);
	}
}

void gn::Scene::AddActor(Actor* actor){
	actors.push_back(actor);
}
