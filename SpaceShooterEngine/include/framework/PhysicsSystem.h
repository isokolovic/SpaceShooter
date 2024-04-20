#pragma once
#include "framework/Core.h"
#include <box2d/b2_world.h>

namespace ss {

	class Actor;
	class PhysicsSystem {
	public:
		static PhysicsSystem& Get();
		void Step(float deltaTime); //Equivalent of Tick function
		b2Body* AddListener(Actor* listener);
		void RemoveListener(b2Body* bodyToRemove);
		float GetPhysicsScale() const { return mPhysicsScale; }
	protected:
		PhysicsSystem();
	private:
		static unique<PhysicsSystem> mPhysicsSystem;
		b2World mPhysicsWorld;
		float mPhysicsScale;
		int mVelocityIterations;
		int mPositionIterations;
	};
}