#include "Enemy/Boss.h"
#include "gameplay/HealthComponent.h"

namespace ss
{
	Boss::Boss(World* world)
		: EnemySpaceship{ world, "SpaceShooterRedux/PNG/Enemies/boss_small.png" },
		mSpeed{ 100.f },
		mSwitchDistanceToEdge{ 100.f },
		mBaseShooterLeft{ this, 1.f, {25.f, -25.f } },
		mBaseShooterRight{ this, 1.f, {25.f, 25.f } }
	{
		SetActorRotation(90.f);
		SetVelocity({ mSpeed, 0.f });
		SetRewardSpawnWeight(0.f);
		HealthComponent& healthComp = GetHealthComponent();
		healthComp.SetInitialHealth(3000.f, 3000.f);
	}

	void Boss::Tick(float deltaTime)
	{
		EnemySpaceship::Tick(deltaTime);
		ShootBaseShooters();
		CheckMove();
	}

	void Boss::CheckMove()
	{
		if (GetActorLocation().x > GetWindowSize().x - mSwitchDistanceToEdge)
		{
			SetVelocity({ -mSpeed, 0.f });
		}
		else if (GetActorLocation().x < mSwitchDistanceToEdge)
		{
			SetVelocity({ mSpeed, 0.f });
		}
	}

	void Boss::ShootBaseShooters()
	{
		mBaseShooterLeft.Shoot();
		mBaseShooterRight.Shoot();
	}
}