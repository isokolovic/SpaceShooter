#include <box2d/b2_body.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_polygon_shape.h>
#include "framework/PhysicsSystem.h"
#include "framework/Actor.h"
#include "framework/MathUtility.h"

namespace ss {

	unique<PhysicsSystem> PhysicsSystem::mPhysicsSystem{ nullptr };

	PhysicsSystem& PhysicsSystem::Get()
	{
		if (!mPhysicsSystem) {
			mPhysicsSystem = std::move(unique<PhysicsSystem>{new PhysicsSystem});
		}

		return *mPhysicsSystem;
	}

	void PhysicsSystem::Step(float deltaTime)
	{
		mPhysicsWorld.Step(deltaTime, mVelocityIterations, mPositionIterations);
	}

	b2Body* PhysicsSystem::AddListener(Actor* listener)
	{
		if (listener->IsPendingDestroy()) return nullptr;

		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(listener); //Pointer to inject the data into b2body (listener)

		bodyDef.position.Set(listener->GetActorLocation().x * GetPhysicsScale(), listener->GetActorLocation().y * GetPhysicsScale());
		bodyDef.angle = DegreesToRatians(listener->GetActorRotation());

		b2Body* body = mPhysicsWorld.CreateBody(&bodyDef);

		b2PolygonShape shape;
		auto bounds = listener->GetActorGlobalBounds();
		shape.SetAsBox(bounds.width / 2.f * GetPhysicsScale(), bounds.height / 2.f * GetPhysicsScale());

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &shape;
		fixtureDef.density = 1.f;
		fixtureDef.friction = 0.3f;
		fixtureDef.isSensor = true;

		body->CreateFixture(&fixtureDef);

		return body;
	}

	PhysicsSystem::PhysicsSystem()
		: mPhysicsWorld{ b2Vec2{0.f, 0.f} },
		mPhysicsScale{ 0.01f }, //Scaling meters to centimeters
		mVelocityIterations{ 8 }, //Values source: box2d documentation
		mPositionIterations{ 3 }
	{
	}
}