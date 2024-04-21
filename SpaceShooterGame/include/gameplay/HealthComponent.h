#pragma once

namespace ss {

	class HealthComponent {

	public:
		HealthComponent(float health, float maxHealth);
		void ChangeHealth(float amt);

		float GetHealth() { return mHealth; }
		float GetMaxHealth() { return mMaxHealth; }
	private:
		void TakenDamage(float amt);
		void HealthEmpty();
		void HealthRegen(float amt);
		float mHealth;
		float mMaxHealth;
	};
}