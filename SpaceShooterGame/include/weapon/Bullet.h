#pragma once
#include "framework/Actor.h"

namespace ss {

	class Bullet : public Actor {
	public:
		Bullet(World* world, Actor* owner, const std::string& texturePath, float speed = 600.f, float damage = 10.f);

		void SetSpeed(float newSpeed);
		void SetDamage(float newDamanage);
		
		virtual void Tick(float deltaTime) override;
		virtual void BeginPlay() override;
	private:
		void Move(float deltaTime);
		Actor* mOwner;
		float mSpeed;
		float mDamage;
	};

}