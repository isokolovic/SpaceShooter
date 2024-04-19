#include "framework/PhysicsSystem.h"

namespace ss {

	unique<PhysicsSystem> PhysicsSystem::mPhysicsSystem{ nullptr };

	PhysicsSystem& PhysicsSystem::Get()
	{
		if (!mPhysicsSystem) {
			mPhysicsSystem = std::move(unique<PhysicsSystem>{new PhysicsSystem});
		}

		return *mPhysicsSystem;
	}

	PhysicsSystem::PhysicsSystem()
		: mPhysicsWorld{b2Vec2{0.f, 0.f}},
		mPhysicsScale{0.01f} //Scaling meters to centimeters
	{
	}
}