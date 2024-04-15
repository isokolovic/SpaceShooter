#include "framework/World.h"
#include "framework/Core.h"
#include "framework/Actor.h"

namespace ss {

	World::World(Application* owningApp) 
		: mOwningApp{owningApp}, 
		mBeganPlay{ false }, 
		mActors{},
		mPendingActors{}{
	}

	void World::BeginPlayInternal()
	{
		if (!mBeganPlay) {
			mBeganPlay = true;
			BeginPlay();
		}
	}

	void World::TickInternal(float deltaTime)
	{
		//Get pending actors in actors at the begining of every tick, and make them play. 
		for (shared<Actor> actor : mPendingActors) {
			mActors.push_back(actor);
			actor->BeginPlayInternal();
		}

		mPendingActors.clear();

		//Make actors play at the begining of every tick
		for (shared<Actor> actor : mActors) {
			actor->Tick(deltaTime);
		}

		Tick(deltaTime);
	}

	World::~World()
	{
	}

	void World::BeginPlay()
	{
		LOG("Began play. ");
	}

	void World::Tick(float deltaTime)
	{
		LOG("Began play at frame rate %f", 1.f / deltaTime);
	}
}