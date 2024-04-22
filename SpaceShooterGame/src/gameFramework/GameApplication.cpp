#include "gameFramework/GameApplication.h"
#include <framework/World.h>
#include "framework/Actor.h"
#include "config.h"
#include "framework/AssetManager.h"
#include "player/PlayerSpaceship.h"

ss::Application* GetApplication()
{
	return new ss::GameApplication{};
}

namespace ss
{
	GameApplication::GameApplication()
		: Application(600, 800, "Space Shooter", sf::Style::Titlebar | sf::Style::Close)
	{
		AssetManager::Get().SetAssetRootDirectory(GetResourceDir());

		weak<World> newWorld = LoadWorld<World>();

		/*newWorld.lock()->SpawnActor<Actor>();*/ //Because it's a weak reference, must be locked first to get a pointer. 
		testPlayerSpaceship = newWorld.lock()->SpawnActor<PlayerSpaceship>();

		testPlayerSpaceship.lock()->SetActorLocation(sf::Vector2f(300.f, 400.f));
		testPlayerSpaceship.lock()->SetActorRotation(-90.f);

		weak<Spaceship> testSpaceShip = newWorld.lock()->SpawnActor<Spaceship>();
		testSpaceShip.lock()->SetTexture("/SpaceShooterRedux/PNG/playerShip1_blue.png");
		testSpaceShip.lock()->SetActorLocation(sf::Vector2f{ 100.f, 50.f });
		testSpaceShip.lock()->SetTeamID(2);

		counter = 0.f;
	}

	void GameApplication::Tick(float deltaTime)
	{
		counter += deltaTime;
	}
}