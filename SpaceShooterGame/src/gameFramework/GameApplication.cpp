#include "gameFramework/GameApplication.h"
#include <framework/World.h>
#include "framework/Actor.h"

ss::Application* GetApplication() {

	return new ss::GameApplication{};
}

namespace ss {
	GameApplication::GameApplication()
		: Application(600, 800, "Space Shooter", sf::Style::Titlebar | sf::Style::Close)
	{
		weak<World> newWorld = LoadWorld<World>();
		newWorld.lock()->SpawnActor<Actor>(); //Because it's a weak reference, must be locked first to get a pointer. 

		actorToDestroy = newWorld.lock()->SpawnActor<Actor>();
		counter = 0;
		actorToDestroy.lock()->Destroy();
	}

	void GameApplication::Tick(float deltaTime)
	{
		counter += deltaTime;
		if (counter > 2.f) { //Test: after 2 sec. destroy an actor
			if (!actorToDestroy.expired()) {
				actorToDestroy.lock()->Destroy();
			}
		}
	}
}