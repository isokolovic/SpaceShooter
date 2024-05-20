#pragma once
#include "framework/Core.h"
#include "player/Player.h"

namespace ss
{
	class PlayerManager
	{
	public:
		Player& CreateNewPlayer();
		Player* GetPlayer(int playerIndex = 0);
		const Player* GetPlayer(int playerIndex = 0) const;
		void Reset();
		static PlayerManager& Get();
	protected:
		PlayerManager();
	private:
		List<Player> mPlayers;
		static unique<PlayerManager> playerManager;
	};
}