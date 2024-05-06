#include "Enemy/HexagonStage.h"
#include "Enemy/TwinBladeStage.h"
#include "Enemy/Vanguard.h"
#include "Enemy/UFO.h"
#include "Enemy/VanguardStage.h"
#include "Enemy/UFOStage.h"
#include "framework/Actor.h"
#include "framework/AssetManager.h"
#include "framework/TimerManager.h"
#include <framework/World.h>
#include "gameplay/GameStage.h"
#include "gameplay/WaitStage.h"
#include "Level/GameLevelOne.h"
#include "player/PlayerManager.h"
#include "player/PlayerSpaceship.h"
#include "widgets/GameplayHUD.h"

namespace ss
{
	GameLevelOne::GameLevelOne(Application* owningApp)
		: World(owningApp)
	{
	}

	void GameLevelOne::BeginPlay()
	{
		Player& newPlayer = PlayerManager::Get().CreateNewPlayer();
		mPlayerSpaceship = newPlayer.SpawnSpaceship(this);
		mPlayerSpaceship.lock()->onActorDestroyed.BindAction(GetWeakRef(), &GameLevelOne::PlayerSpaceshipDestroyed);
		mGameplayHUD = SpawnHUD<GameplayHUD>();
	}

	void GameLevelOne::InitGameStages()
	{
		AddStage(shared<UFOStage>{new UFOStage{ this }});

		AddStage(shared<WaitStage>{new WaitStage{ this, 3.f }});
		AddStage(shared<VanguardStage>{new VanguardStage{ this }});

		AddStage(shared<WaitStage>{new WaitStage{ this, 5.f }});
		AddStage(shared<TwinBladeStage>{new TwinBladeStage{ this }});

		AddStage(shared<WaitStage>{new WaitStage{ this, 5.f }});
		AddStage(shared<HexagonStage>{new HexagonStage{ this }});
	}

	void GameLevelOne::PlayerSpaceshipDestroyed(Actor* destroyedShip)
	{
		mPlayerSpaceship = PlayerManager::Get().GetPlayer()->SpawnSpaceship(this);

		if (!mPlayerSpaceship.expired())
		{
			mPlayerSpaceship.lock()->onActorDestroyed.BindAction(GetWeakRef(), &GameLevelOne::PlayerSpaceshipDestroyed);
		}
		else
		{
			GameOver();
		}
	}

	void GameLevelOne::GameOver()
	{
		LOG("Game over.");
	}
}