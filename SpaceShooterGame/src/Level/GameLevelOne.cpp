#include "Enemy/Vanguard.h"
#include <framework/World.h>
#include "framework/Actor.h"
#include "framework/AssetManager.h"
#include "framework/TimerManager.h"
#include "gameplay/GameStage.h"
#include "Level/GameLevelOne.h"
#include "player/PlayerSpaceship.h"

namespace ss
{
	GameLevelOne::GameLevelOne(Application* owningApp)
		: World(owningApp)
	{
		/*newWorld.lock()->SpawnActor<Actor>();*/ //Because it's a weak reference, must be locked first to get a pointer. 
		testPlayerSpaceship = SpawnActor<PlayerSpaceship>();
		testPlayerSpaceship.lock()->SetActorLocation(sf::Vector2f(300.f, 400.f));
		testPlayerSpaceship.lock()->SetActorRotation(-90.f);

		weak<Vanguard> testSpaceShip = SpawnActor<Vanguard>();
		testSpaceShip.lock()->SetActorLocation(sf::Vector2f{ 100.f, 50.f });
	}

	void GameLevelOne::BeginPlay()
	{
		timerHandle_Test = TimerManager::Get().SetTimer(GetWeakRef(), &GameLevelOne::TimerCallback_Test, 2, true);
	}

	void GameLevelOne::TimerCallback_Test()
	{
		LOG("Callback called.");
		TimerManager::Get().ClearTimer(timerHandle_Test);
	}

	void GameLevelOne::InitGameStages()
	{
		AddStage(shared<GameStage>{new GameStage{ this }});
	}
}