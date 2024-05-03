#include "framework/World.h"
#include "player/Reward.h"
#include "player/PlayerSpaceship.h"
#include "weapon/ThreeWayShooter.h"
#include "weapon/FrontalWiper.h"

namespace ss
{
	Reward::Reward(World* world, const std::string& texturePath, RewardFunc rewardFunc, float speed)
		: Actor{ world, texturePath },
		mRewardFunc{ rewardFunc },
		mSpeed{ speed }
	{
	}

	void Reward::BeginPlay()
	{
		Actor::BeginPlay();
		SetEnablePhysics(true);
	}

	void Reward::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);
		AddActorLocationOffset({ 0.f, mSpeed * deltaTime });
	}

	void Reward::OnActorBeginOverlap(Actor* otherActor)
	{
		//TODO clean-up casting
		PlayerSpaceship* playerSpaceship = static_cast<PlayerSpaceship*>(otherActor);

		if (playerSpaceship != nullptr && !playerSpaceship->IsPendingDestroy())
		{
			mRewardFunc(playerSpaceship);
		}
	}

	weak<Reward> CreateHealthReward(World* world)
	{
		return CreateReward(world, "SpaceShooterRedux/PNG/Power-ups/pill_green.png", RewardHealth);
	}

	weak<Reward> CreateThreeWayShooterRevard(World* world)
	{
		return CreateReward(world, "SpaceShooterRedux/PNG/Power-ups/powerupRed_star.png", RewardThreeWayShooter);
	}

	weak<Reward> CreateFrontalWiperReward(World* world)
	{
		return CreateReward(world, "SpaceShooterRedux/PNG/Power-ups/powerupYellow_star.png", RewardFrontalWiper);
	}

	weak<Reward> CreateReward(World* world, const std::string& texturePath, RewardFunc rewardFunc)
	{
		weak<Reward> reward = world->SpawnActor<Reward>(texturePath, rewardFunc);
		return reward;
	}

	void RewardHealth(PlayerSpaceship* player)
	{
		static float rewartAmt = 10.f;

		if (player && !player->IsPendingDestroy())
		{
			player->GetHealthComponent().ChangeHealth(rewartAmt);
		}
	}

	void RewardThreeWayShooter(PlayerSpaceship* player)
	{
		if (player && !player->IsPendingDestroy())
		{
			player->SetShooter(unique<Shooter>{new ThreeWayShooter{ player, 0.4, {50.f, 0.f} }});
		}
	}

	void RewardFrontalWiper(PlayerSpaceship* player)
	{
		if (player && !player->IsPendingDestroy())
		{
			player->SetShooter(unique<Shooter>{new FrontalWiper{ player, 0.4, {50.f, 0.f} }});
		}
	}
}