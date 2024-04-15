#include "gameFramework/GameApplication.h"
#include <framework/World.h>
#include "framework/Actor.h"

ss::Application* GetApplication() {

	return new ss::GameApplication{};
}

namespace ss {
	GameApplication::GameApplication()
	{
		weak<World> newWorld = LoadWorld<World>();
		newWorld.lock()->SpawnActor<Actor>(); //Because it's a weak reference, must be locked first
	}
}