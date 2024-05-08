#pragma once
#include "spaceship/Spaceship.h"
#include "player/Reward.h"
namespace ss
{

	class EnemySpaceship : public Spaceship
	{
	public:
		EnemySpaceship(World* owningWorld, std::string texturePath, float collisionDamage = 200.f, float mRewardSpawnRate = 0.5f,
			const List<RewardFactoryFunc> rewards =
			{
				CreateHealthReward,
				CreateThreeWayShooterRevard,
				CreateFrontalWiperReward,
				CreateLifeReward
			}
		);
		virtual void Tick(float deltaTime) override;
		void SetScoreAwardAmt(unsigned int amt);
	private:
		void SpawnReward();
		float mRewardSpawnRate;
		float mCollisionDamage;
		unsigned int mScoreAwardAmt;
		virtual void OnActorBeginOverlap(Actor* other) override;
		virtual void Blew() override;
		List<RewardFactoryFunc> mRewardFactoryFunc;
	};
}