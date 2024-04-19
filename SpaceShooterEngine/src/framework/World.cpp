#include "framework/World.h"
#include "framework/Core.h"
#include "framework/Actor.h"
#include "framework/Application.h"

namespace ss {

	World::World(Application* owningApp)
		: mOwningApp{ owningApp },
		mBeganPlay{ false },
		mActors{},
		mPendingActors{} {
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
		for (auto iter = mActors.begin(); iter != mActors.end();) {
			iter->get()->TickInternal(deltaTime);
			++iter;
		}


		for (shared<Actor> actor : mActors) {
			actor->Tick(deltaTime);
		}

		Tick(deltaTime);
	}

	void World::Render(sf::RenderWindow& window)
	{
		for (auto actor : mActors) {
			actor->Render(window);
		}
	}

	World::~World()
	{
	}

	sf::Vector2u World::GetWindowSize() const
	{
		return mOwningApp->GetWindowSize();
	}

	void World::CleanCycle()
	{
		for (auto iter = mActors.begin(); iter != mActors.end();) {
			if (iter->get()->IsPendingDestroy()) {
				iter = mActors.erase(iter);//Removing from Actors vector (which were sent pending destroy in previous loop)
			}
			else {
				++iter;
			}
		}
	}

	void World::BeginPlay()
	{
		//LOG("Began play. ");
	}

	void World::Tick(float deltaTime)
	{
		//LOG("Began play at frame rate %f", 1.f / deltaTime);
	}
}