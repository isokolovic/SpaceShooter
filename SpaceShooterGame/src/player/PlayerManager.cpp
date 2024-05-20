#include "player/PlayerManager.h"

namespace ss
{
	unique<PlayerManager> PlayerManager::playerManager{ nullptr };

	PlayerManager::PlayerManager()
	{
	}

	Player& PlayerManager::CreateNewPlayer()
	{
		mPlayers.emplace(mPlayers.begin(), Player());
		return mPlayers.back();
	}

	Player* PlayerManager::GetPlayer(int playerIndex)
	{
		if (playerIndex >= 0 && playerIndex <= mPlayers.size())
		{
			return &mPlayers[playerIndex];
		}

		return nullptr;
	}

	const Player* PlayerManager::GetPlayer(int playerIndex) const
	{
		if (playerIndex >= 0 && playerIndex <= mPlayers.size())
		{
			return &mPlayers[playerIndex];
		}

		return nullptr;
	}

	void PlayerManager::Reset()
	{
		mPlayers.clear();
	}

	PlayerManager& PlayerManager::Get()
	{
		if (!playerManager)
		{
			playerManager = std::move(unique<PlayerManager>{new PlayerManager{}});
		}

		return *playerManager;
	}
}