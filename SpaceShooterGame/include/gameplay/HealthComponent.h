#pragma once
#include "framework/Delegate.h"

namespace ss {

	class HealthComponent {

	public:
		HealthComponent(float health, float maxHealth);
		void ChangeHealth(float amt);

		float GetHealth() { return mHealth; }
		float GetMaxHealth() { return mMaxHealth; }

		Delegate<float, float, float> onHealthChanged;
	private:
		void TakenDamage(float amt);
		void HealthEmpty();
		void HealthRegen(float amt);
		float mHealth;
		float mMaxHealth;
	};
}