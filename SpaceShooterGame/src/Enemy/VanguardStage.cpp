#include "Enemy/Vanguard.h"
#include "Enemy/VanguardStage.h"
#include "framework/World.h"

namespace ss
{
	VanguardStage::VanguardStage(World* world)
		: GameStage{ world },
		mSpawnInterval{ 2.f },
		mSwitchInterval{ 5.f },
		mSpawnDistanceToEdge{ 100.f },
		mLeftSpawnLocation{ 0.0f, 0.0f },
		mRightSpawnLocation{ 0.0f, 0.0f },
		mSpawnLocation{ 0.0f, 0.0f },
		mRowsToSpawn{ 2 },
		mRowSpawnCount{ 0 },
		mVanguardsPerRow{ 5 },
		mCurrentRowVanguardCount{ 0 }
	{
	}

	void VanguardStage::StartStage()
	{
		auto windowSize = GetWorld()->GetWindowSize();
		mLeftSpawnLocation = sf::Vector2f{ mSpawnDistanceToEdge, -100.f };
		mRightSpawnLocation = sf::Vector2f{ windowSize.x - mSpawnDistanceToEdge, -100.f };

		SwitchRow();
	}

	void VanguardStage::StageFinished()
	{
		TimerManager::Get().ClearTimer(mSpawnTimerHandle);
		TimerManager::Get().ClearTimer(mSwitchTimerHandle);
	}

	void VanguardStage::SpawnVanguard()
	{
		weak<Vanguard> newVanguard = GetWorld()->SpawnActor<Vanguard>();
		newVanguard.lock()->SetActorLocation(mSpawnLocation);
		++mCurrentRowVanguardCount;

		if (mCurrentRowVanguardCount == mVanguardsPerRow)
		{
			TimerManager::Get().ClearTimer(mSpawnTimerHandle);
			mSwitchTimerHandle = TimerManager::Get().SetTimer(GetWeakRef(), &VanguardStage::SwitchRow, mSwitchInterval, false);

			mCurrentRowVanguardCount = 0;
		}
	}

	void VanguardStage::SwitchRow()
	{
		if (mRowSpawnCount == mRowsToSpawn)
		{
			FinishStage();
			return;
		}

		if (mSpawnLocation == mLeftSpawnLocation)
		{
			mSpawnLocation = mRightSpawnLocation;
		}
		else
		{
			mSpawnLocation = mLeftSpawnLocation;
		}

		mSpawnTimerHandle = TimerManager::Get().SetTimer(GetWeakRef(), &VanguardStage::SpawnVanguard, mSpawnInterval, true);

		++mRowSpawnCount;
	}
}