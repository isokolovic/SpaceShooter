#include "framework/Actor.h"
#include "framework/Core.h"

namespace ss {

	Actor::Actor(World* owningWorld)
		:mowningWorld{ owningWorld }, 
		mHasBeganPlay{ false } 
	{
	}

	Actor::~Actor()
	{
		LOG("Actor destroyed.");
	}

	void Actor::BeginPlayInternal()
	{
		if (!mHasBeganPlay) {
			mHasBeganPlay = true;
			BeginPlay();
		}
	}

	void Actor::BeginPlay()
	{
		LOG("Actor began playing. ");
	}

	void Actor::Tick(float deltaTime)
	{
		LOG("Actor ticking. ");
	}
}