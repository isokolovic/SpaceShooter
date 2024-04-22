#include "weapon/Shooter.h"

namespace ss {

	void Shooter::Shoot()
	{
		if (CanShoot() && !IsOnCooldown()) {
			ShootImpl();
		}
	}

	Shooter::Shooter(Actor* owner)
		:mOwner{ owner }
	{
	}
}