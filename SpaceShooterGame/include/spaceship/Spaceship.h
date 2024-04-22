#pragma once
#include "framework/Actor.h"
#include "gameplay/HealthComponent.h"

namespace ss {

	class Spaceship : public Actor
	{

	public:
		Spaceship(World* owningWorld, const std::string& texturePath = "");

		virtual void Tick(float deltaTime) override;
		void SetVelocity(const sf::Vector2f& newVelocity);
		sf::Vector2f GetVelocity() const { return mVelocity; }
		virtual void Shoot();
		virtual void BeginPlay() override;
		virtual void ApplyDamage(float amt) override;
	private:
		virtual void OnHealthChanged(float amt, float health, float maxHealth);
		virtual void OnTakenDamage(float amt, float health, float maxHealth);
		virtual void BlowUp();

		sf::Vector2f mVelocity;
		HealthComponent mHealthComponent;
	};
}