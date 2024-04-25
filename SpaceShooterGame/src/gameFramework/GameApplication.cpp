#include "gameFramework/GameApplication.h"
#include <Level/GameLevelOne.h>
#include "config.h"
#include "framework/AssetManager.h"

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
		weak<GameLevelOne> newWorld = LoadWorld<GameLevelOne>();
	}
}