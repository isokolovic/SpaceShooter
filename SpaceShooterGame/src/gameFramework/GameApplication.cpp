#include "gameFramework/GameApplication.h"
#include <framework/World.h>

ss::Application* GetApplication() {

	return new ss::GameApplication{};
}

namespace ss {
	GameApplication::GameApplication()
	{
		LoadWorld<World>();
	}
}