#pragma once
#include "Enemy/EnemySpaceship.h"

namespace ss
{
	class Boss : public EnemySpaceship
	{
	public:
		Boss(World* world);
		virtual void Tick(float deltaTime) override;
	private:
		float mSpeed;
		float mSwitchDistanceToEdge;
		void CheckMove();
	};
}