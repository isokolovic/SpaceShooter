#pragma once
#include "framework/Object.h"
#include "framework/Delegate.h"

namespace ss
{
	class World;

	class GameStage : public Object
	{
	public:
		GameStage(World* world);
		const World* GetWorld() const { return mWorld; }
		World* GetWorld() { return mWorld; }

		Delegate<> onStageFinished;

		virtual void StartStage();
		virtual void TickStage(float deltaTime);
		void FinishStage();
		bool isStageFinished() const { return mStageFinished; }
	private:
		World* mWorld;
		bool mStageFinished;
		virtual void StageFinished();
	};
}