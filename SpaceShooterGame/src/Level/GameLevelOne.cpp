#include "Enemy/Vanguard.h"
#include "Enemy/VanguardStage.h"
#include "Enemy/TwinBladeStage.h"
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
	}

	void GameLevelOne::BeginPlay()
	{
	}

	void GameLevelOne::InitGameStages()
	{
		AddStage(shared<TwinBladeStage>{new TwinBladeStage{ this }});
		AddStage(shared<VanguardStage>{new VanguardStage{ this }});
	}
}