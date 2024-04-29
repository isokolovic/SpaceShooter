#pragma once
#include <SFML/Graphics.hpp>
#include "framework/TimerManager.h"
#include "gameplay/GameStage.h"

namespace ss
{
	class HexagonStage : public GameStage
	{
	public:
		HexagonStage(World* world);
		virtual void StartStage() override;
	private:
		virtual void StageFinished() override;
		void SpawnHexagon();

		float mSpawnInterval;
		float mSideSpawnOffset;
		int mSpawnGroupAmount;
		int mCurrentSpawnCount;

		sf::Vector2f mMidSpawnLocation;
		sf::Vector2f mLeftSpawnLocation;
		sf::Vector2f mRightSpawnLocation;

		TimerHandle mSpawnTimer;
	};
}