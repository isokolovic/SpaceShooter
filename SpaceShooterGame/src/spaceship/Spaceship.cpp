#include "spaceship/Spaceship.h"
#include <functional>

namespace ss {

	Spaceship::Spaceship(World* owningWorld, const std::string& texturePath)
		: Actor{ owningWorld, texturePath },
		mVelocity{},
		mHealthComponent{ 100.f, 100.f }
	{
	}

	void Spaceship::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);
		AddActorLocationOffset(GetVelocity() * deltaTime);
	}

	void Spaceship::SetVelocity(const sf::Vector2f& newVelocity)
	{
		mVelocity = newVelocity;
	}

	void Spaceship::Shoot()
	{
	}

	void Spaceship::BeginPlay()
	{
		Actor::BeginPlay();
		SetEnablePhysics(true);

		mHealthComponent.onHealthChanged.BindAction(GetWeakRef(), &Spaceship::OnHealthChanged);
		mHealthComponent.onTakenDamage.BindAction(GetWeakRef(), &Spaceship::OnTakenDamage);
		mHealthComponent.onHealthEmpty.BindAction(GetWeakRef(), &Spaceship::BlowUp);

		//mHealthComponent.onHealthChanged.Broadcast(11, 89, 100);
	}

	void Spaceship::ApplyDamage(float amt)
	{
		mHealthComponent.ChangeHealth(-amt);
		LOG("Dealt %f damage", amt);
	}

	void Spaceship::OnHealthChanged(float amt, float health, float maxHealth)
	{
		LOG("Health changed by %f, and now is %f/%f", amt, health, maxHealth);
	}

	void Spaceship::OnTakenDamage(float amt, float health, float maxHealth)
	{
		LOG("Taken %f damage, now health is %f/%f", amt, health, maxHealth);
	}

	void Spaceship::BlowUp()
	{
		Destroy();
	}
}