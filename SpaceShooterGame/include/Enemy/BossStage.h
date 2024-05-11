#pragma once
#include "gameplay/GameStage.h"

namespace ss
{
	class Actor;

	class BossStage : public GameStage
	{
	public:
		BossStage(World* world);
		virtual void StartStage() override;
	private:
		void BossDestroyed(Actor* bossActor);
	};
}