#include "Enemy/EnemySpaceship.h"
#include "framework/MathUtility.h"
#include "player/Player.h"
#include "player/PlayerManager.h"

namespace ss
{
	EnemySpaceship::EnemySpaceship(World* owningWorld, std::string texturePath, float collisionDamage, float rewardSpawnRate, const List<RewardFactoryFunc> rewards)
		: Spaceship(owningWorld, texturePath), mCollisionDamage{ collisionDamage }, mRewardFactoryFunc{ rewards }, mScoreAwardAmt{ 10 }, mRewardSpawnRate{ rewardSpawnRate }
	{
		SetTeamID(2);
	}

	void EnemySpaceship::Tick(float deltaTime)
	{
		Spaceship::Tick(deltaTime);

		if (IsActorOutOfWindowBounds(GetActorGlobalBounds().width * 2.f)) Destroy();
	}

	void EnemySpaceship::SetScoreAwardAmt(unsigned int amt)
	{
		mScoreAwardAmt = amt;
	}

	void EnemySpaceship::SetRewardSpawnWeight(float weight)
	{
		if (weight < 0 || weight > 1)
		{
			return;
		}

		mRewardSpawnRate = weight;
	}

	void EnemySpaceship::SpawnReward()
	{
		if (mRewardFactoryFunc.size() == 0) return;

		if (mRewardSpawnRate < RandomRange(0, 1)) return; //Don't spawn always

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

		Player* player = PlayerManager::Get().GetPlayer();
		if (player)
		{
			player->AddScore(mScoreAwardAmt);
		}
	}
}