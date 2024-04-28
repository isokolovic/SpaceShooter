#include  "gameplay/GameStage.h"
#include "framework/Core.h"

namespace ss
{
	GameStage::GameStage(World* world)
		: mWorld{ world },
		mStageFinished{ false }
	{

	}

	void GameStage::StartStage()
	{
		LOG("Stage started.");
	}

	void GameStage::TickStage(float deltaTime)
	{
		LOG("Stage sticking.");
	}

	void GameStage::FinishStage()
	{
		onStageFinished.Broadcast();
		mStageFinished = true;
		StageFinished();
	}

	void GameStage::StageFinished()
	{
		LOG("Stage finished.");
	}
}