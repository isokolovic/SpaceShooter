#include "Enemy/UFO.h"
#include "Enemy/UFOStage.h"
#include "framework/MathUtility.h"
#include "framework/World.h"

namespace ss
{
	UFOStage::UFOStage(World* world)
		: GameStage{ world },
		mSpawnInterval{ 4.f },
		mSpawnAmount{ 10 },
		mCurrentSpawnAmount{ 0 },
		mUFOSpeed{ 200.f }
	{
	}

	void UFOStage::StartStage()
	{
		mSpawnTimer = TimerManager::Get().SetTimer(GetWeakRef(), &UFOStage::SpawnUFO, mSpawnInterval, true);
	}

	void UFOStage::StageFinished()
	{
		TimerManager::Get().ClearTimer(mSpawnTimer);
	}

	sf::Vector2f UFOStage::GetRandomSpawnLocation() const
	{
		auto windowSize = GetWorld()->GetWindowSize();
		float spawnLeft = RandomRange(-1, 1);
		float spawnLocX = 0;

		if (spawnLeft < 0)
		{
			spawnLocX = windowSize.x + 100.f;
		}
		else
		{
			spawnLocX = -100.f;
		}

		float spawnLocY = RandomRange(0, windowSize.y);
		return sf::Vector2f{ spawnLocX, spawnLocY };
	}

	void UFOStage::SpawnUFO()
	{
		sf::Vector2f spawnLocation = GetRandomSpawnLocation();
		auto windowSize = GetWorld()->GetWindowSize();
		sf::Vector2f center{ windowSize.x / 2.f, windowSize.y / 2.f };
		sf::Vector2f spawnLocationToCenter{ center.x - spawnLocation.x, center.y - spawnLocation.y };
		Normalize(spawnLocationToCenter);

		sf::Vector2f spawnVelocity = spawnLocationToCenter * mUFOSpeed;

		weak<UFO> newUfo = GetWorld()->SpawnActor<UFO>(spawnVelocity);
		newUfo.lock()->SetActorLocation(spawnLocation);

		if (++mCurrentSpawnAmount == mSpawnAmount)
		{
			FinishStage();
		}
	}
}