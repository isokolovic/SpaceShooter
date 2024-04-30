#include "Enemy/HexagonStage.h"
#include "Enemy/TwinBladeStage.h"
#include "Enemy/Vanguard.h"
#include "Enemy/UFO.h"
#include "Enemy/VanguardStage.h"
#include "framework/Actor.h"
#include "framework/AssetManager.h"
#include "framework/TimerManager.h"
#include <framework/World.h>
#include "gameplay/GameStage.h"
#include "gameplay/WaitStage.h"
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
		weak<UFO> testUfo = SpawnActor<UFO>(sf::Vector2f{ 0.f, 0.f });
		testUfo.lock()->SetActorLocation({ GetWindowSize().x / 2.f, GetWindowSize().y / 2.f });
	}

	void GameLevelOne::InitGameStages()
	{
		AddStage(shared<WaitStage>{new WaitStage{ this, 3.f }});
		AddStage(shared<VanguardStage>{new VanguardStage{ this }});

		AddStage(shared<WaitStage>{new WaitStage{ this, 5.f }});
		AddStage(shared<TwinBladeStage>{new TwinBladeStage{ this }});

		AddStage(shared<WaitStage>{new WaitStage{ this, 5.f }});
		AddStage(shared<HexagonStage>{new HexagonStage{ this }});
	}
}