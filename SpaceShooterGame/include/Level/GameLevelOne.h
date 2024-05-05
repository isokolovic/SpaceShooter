#pragma once
#include "framework/World.h"
#include "framework/TimerManager.h"

namespace ss
{
	class PlayerSpaceship;
	class GameplayHUD;

	class GameLevelOne : public World
	{
	public:
		GameLevelOne(Application* owningApp);
	private:
		virtual void BeginPlay() override;
		weak<PlayerSpaceship> mPlayerSpaceship;
		weak<GameplayHUD> mGameplayHUD;
		TimerHandle timerHandle_Test;
		virtual void InitGameStages() override;
		void PlayerSpaceshipDestroyed(Actor* destroyedShip);
		void GameOver();
	};
}