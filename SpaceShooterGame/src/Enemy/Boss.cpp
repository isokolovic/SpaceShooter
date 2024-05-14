#include "Enemy/Boss.h"
#include "gameplay/HealthComponent.h"

namespace ss
{
	Boss::Boss(World* world)
		: EnemySpaceship{ world, "SpaceShooterRedux/PNG/Enemies/boss_small.png" },
		mSpeed{ 100.f },
		mBaseSpeed{ 100.f },
		mSwitchDistanceToEdge{ 100.f },
		mBaseShooterLeft{ this, 1.f, {25.f, -25.f } },
		mBaseShooterRight{ this, 1.f, {25.f, 25.f } },
		mThreeWayShooter{ this, 4.f, {50.f, 25.f } },
		mFrontalWiperLeft{ this, 5.f, {40.f, -50.f } },
		mFrontalWiperRight{ this, 5.f, {40.f, 50.f } },
		mStage{ 1 }
	{
		SetActorRotation(90.f);
		SetVelocity({ mSpeed, 0.f });
		SetRewardSpawnWeight(0.f);
	}

	void Boss::Tick(float deltaTime)
	{
		EnemySpaceship::Tick(deltaTime);
		ShootBaseShooters();
		ShootFrontalWipers();
		ShootThreeWayShooter();
		CheckMove();
	}

	void Boss::BeginPlay()
	{
		EnemySpaceship::BeginPlay();
		HealthComponent& healthComp = GetHealthComponent();
		healthComp.SetInitialHealth(3000.f, 3000.f);
		healthComp.onHealthChanged.BindAction(GetWeakRef(), &Boss::HealthChanged);
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

	void Boss::ShootThreeWayShooter()
	{
		mThreeWayShooter.Shoot();
	}

	void Boss::ShootFrontalWipers()
	{
		mFrontalWiperLeft.Shoot();
		mFrontalWiperRight.Shoot();
	}

	void Boss::HealthChanged(float amt, float currentHealth, float maxHealth)
	{
		float percentLefth = currentHealth / maxHealth;

		if (percentLefth < 0.7 && percentLefth > 0.5)
		{
			SetStage(2);
		}
		if (percentLefth < 0.5 && percentLefth > 0.3)
		{
			SetStage(3);
		}
		if (percentLefth < 0.3)
		{
			SetStage(4);
		}
	}

	void Boss::SetStage(int newStage)
	{
		mStage = newStage;
		mBaseShooterLeft.SetCurrentLevel(mStage);
		mBaseShooterRight.SetCurrentLevel(mStage);
		mFrontalWiperLeft.SetCurrentLevel(mStage);
		mFrontalWiperRight.SetCurrentLevel(mStage);
		mThreeWayShooter.SetCurrentLevel(mStage);
		mSpeed *= mStage * mBaseSpeed;
	}
}