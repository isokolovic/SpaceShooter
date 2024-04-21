#include "gameplay/HealthComponent.h"
#include "framework/Core.h"

namespace ss {

	HealthComponent::HealthComponent(float health, float maxHealth)
		: mHealth{ health },
		mMaxHealth{ maxHealth }
	{

	}

	void HealthComponent::ChangeHealth(float amt)
	{
		if (amt == 0) return;
		if (mHealth = 0) return; //Dead

		mHealth += amt;
		if (mHealth < 0)
		{
			mHealth = 0;
		}

		if (mHealth > mMaxHealth)
		{
			mHealth = mMaxHealth;
		}

		if (mHealth > mMaxHealth)
		{

		}

		if (amt < 0)
		{
			TakenDamage(-amt);
			if (mHealth <= 0)
			{
				HealthEmpty();
			}
		}
		else
		{
			HealthRegen(amt);
		}
	}

	void HealthComponent::TakenDamage(float amt)
	{
		LOG("Took damage %f, now health is: %f/%f ", amt, mHealth, mMaxHealth);
	}

	void HealthComponent::HealthEmpty()
	{
		LOG("Deat");
	}

	void HealthComponent::HealthRegen(float amt)
	{
		LOG("Health regened %f, now health is: %f/%f ", amt, mHealth, mMaxHealth);

	}
}