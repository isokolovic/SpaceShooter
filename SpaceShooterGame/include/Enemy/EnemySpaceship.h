#pragma once
#include "spaceship/Spaceship.h"
#include "player/Reward.h"
namespace ss
{

	class EnemySpaceship : public Spaceship
	{
	public:
		EnemySpaceship(World* owningWorld, std::string texturePath, float collisionDamage = 200.f,
			const List<RewardFactoryFunc> rewards =
			{
				CreateHealthReward,
				CreateThreeWayShooterRevard,
				CreateFrontalWiperReward
			}
		);
		virtual void Tick(float deltaTime) override;
	private:
		void SpawnReward();
		float mCollisionDamage;
		virtual void OnActorBeginOverlap(Actor* other) override;
		virtual void Blew() override;
		List<RewardFactoryFunc> mRewardFactoryFunc;
	};
}