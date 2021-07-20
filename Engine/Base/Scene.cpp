#include "Scene.h"
#include "Actor.h"

namespace gn {
	void Scene::Update(float dt) {
		//Add new actors
		actors.insert(actors.end(), std::make_move_iterator(newActors.begin()), std::make_move_iterator(newActors.end()));
		newActors.clear();
		//Update actors
		for (auto& actor : actors) {
			actor->Update(dt);
		}

		//check collisions
		for (size_t i = 0; i < actors.size(); i++) {
			for (size_t j = i + 1; j < actors.size(); j++) {
				gn::Vector2 dir = actors[i]->transform.position - actors[j]->transform.position;
				float distance = dir.Length();
				if (distance < 40) {
					actors[i]->OnCollision(actors[j].get());
					actors[j]->OnCollision(actors[i].get());
				}
			}
		}

		//destroy actors
		auto iter = actors.begin();
		while (iter != actors.end()) {
			if ((*iter)->destroy) {
				iter = actors.erase(iter); // Equals so that when it gets removed it grabs and sets up the next iter. Instead of stopping
			}
			else {
				iter++;
			}
		}
	}

	void Scene::Draw(Core::Graphics& graphics) {
		for (auto& actor : actors) {
			actor->Draw(graphics);
		}
	}

	void Scene::AddActor(std::unique_ptr<Actor> actor) {
		actor.get()->scene = this;
		newActors.push_back(std::move(actor));
	}

	void Scene::RemoveActor(Actor* actor) {

	}

	void Scene::RemoveAllActors() {
		actors.clear();
	}

}