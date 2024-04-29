#pragma once
#include "framework/TimerManager.h"
#include "gameplay/GameStage.h"
#include "Enemy/Hexagon.h"
#include "SFML/Graphics.hpp"

namespace ss
{
	class VanguardStage : public GameStage
	{
	public:
		VanguardStage(World* world);
		virtual void StartStage() override;
	private:
		float mSpawnInterval;
		float mSwitchInterval;
		float mSpawnDistanceToEdge;

		sf::Vector2f mLeftSpawnLocation;
		sf::Vector2f mRightSpawnLocation;
		sf::Vector2f mSpawnLocation;

		TimerHandle mSpawnTimerHandle;
		TimerHandle mSwitchTimerHandle;

		int mRowsToSpawn;
		int mRowSpawnCount;

		int mVanguardsPerRow;
		int mCurrentRowVanguardCount;

		virtual void StageFinished() override;
		void SpawnVanguard();
		void SwitchRow();
	};
}