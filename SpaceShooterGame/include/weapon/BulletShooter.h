#pragma once
#include <SFML/System.hpp>
#include "weapon/Shooter.h"

namespace ss {

	class BulletShooter : public Shooter {
	public:
		BulletShooter(Actor* owner, float cooldownTime = 1.f);
		bool IsOnCooldown() const override;
	private:
		virtual void ShootImpl() override;
		sf::Clock mCooldownClock;
		float mCooldownTime;
	};
}