#pragma once
#include "framework/World.h"

namespace ss
{
	class PlayerSpaceship;

	class GameLevelOne : public World
	{
	public:
		GameLevelOne(Application* owningApp);
	private:
		weak<PlayerSpaceship> testPlayerSpaceship;
	};
}