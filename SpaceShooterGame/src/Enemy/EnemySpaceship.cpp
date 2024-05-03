#include "Enemy/EnemySpaceship.h"
#include "framework/MathUtility.h"

namespace ss
{
	EnemySpaceship::EnemySpaceship(World* owningWorld, std::string texturePath, float collisionDamage, const List<RewardFactoryFunc> rewards)
		: Spaceship(owningWorld, texturePath), mCollisionDamage{ collisionDamage }, mRewardFactoryFunc{ rewards }
	{
		SetTeamID(2);
	}

	void EnemySpaceship::Tick(float deltaTime)
	{
		Spaceship::Tick(deltaTime);

		if (IsActorOutOfWindowBounds(GetActorGlobalBounds().width * 2.f)) Destroy();
	}

	void EnemySpaceship::SpawnReward()
	{
		if (mRewardFactoryFunc.size() == 0) return;

		int pick = (int)RandomRange(0, mRewardFactoryFunc.size());
		if (pick >= 0 && pick < mRewardFactoryFunc.size())
		{
			weak<Reward> newReward = mRewardFactoryFunc[pick](GetWorld());
			newReward.lock()->SetActorLocation(GetActorLocation());
		}
	}

	void EnemySpaceship::OnActorBeginOverlap(Actor* other)
	{
		Spaceship::OnActorBeginOverlap(other);

		if (IsOtherHostile(other))
		{
			other->ApplyDamage(mCollisionDamage);
		}
	}

	void EnemySpaceship::Blew()
	{
		SpawnReward();
	}
}