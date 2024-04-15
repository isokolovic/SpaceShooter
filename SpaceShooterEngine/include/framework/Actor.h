#pragma once

namespace ss {

	class World;

	class Actor {

	public:
		Actor(World* owningWorld);

		void BeginPlayInternal();
		virtual void BeginPlay();
		virtual void Tick(float deltaTime);

	private:
		World* mowningWorld;
		bool mHasBeganPlay;
	};
}