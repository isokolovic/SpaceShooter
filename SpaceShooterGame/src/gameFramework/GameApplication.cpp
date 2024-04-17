#include "gameFramework/GameApplication.h"
#include <framework/World.h>
#include "framework/Actor.h"
#include "config.h"

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
		actorToDestroy.lock()->SetTexture(GetResourceDir() + "/SpaceShooterRedux/PNG/playerShip1_blue.png");

		actorToDestroy.lock()->SetActorLocation(sf::Vector2f(300.f, 400.f));
		actorToDestroy.lock()->SetActorRotation(180.f);

		counter = 0;
	}

	void GameApplication::Tick(float deltaTime)
	{
		//counter += deltaTime;
		//if (counter > 2.f) { //Test: after 2 sec. destroy an actor
		//	if (!actorToDestroy.expired()) {
		//		actorToDestroy.lock()->Destroy();
		//	}
		//}
	}
}