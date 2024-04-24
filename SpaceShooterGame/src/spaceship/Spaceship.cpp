#include <functional>
#include "spaceship/Spaceship.h"
#include "framework/MathUtility.h"
#include "VFX/Explosion.h"

namespace ss {

	Spaceship::Spaceship(World* owningWorld, const std::string& texturePath)
		: Actor{ owningWorld, texturePath },
		mVelocity{},
		mHealthComponent{ 100.f, 100.f },
		mBlinkTime{ 0.f },
		mBlinkDuration{ 0.2f },
		mBlinkColorOffset{ 255, 0, 0, 255 }
	{
	}

	void Spaceship::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);
		AddActorLocationOffset(GetVelocity() * deltaTime);
		UpdateBlink(deltaTime);
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
	}

	void Spaceship::ApplyDamage(float amt)
	{
		mHealthComponent.ChangeHealth(-amt);
	}

	void Spaceship::OnHealthChanged(float amt, float health, float maxHealth)
	{
	}

	void Spaceship::OnTakenDamage(float amt, float health, float maxHealth)
	{
		Blink();
	}

	void Spaceship::BlowUp()
	{
		Explosion* exp = new Explosion();
		exp->SpawnExplosion(GetWorld(), GetActorLocation());
		Destroy();
		delete exp;
	}

	void Spaceship::Blink()
	{
		if (mBlinkTime == 0)
		{
			mBlinkTime = mBlinkDuration;
		}
	}

	void Spaceship::UpdateBlink(float deltaTime)
	{
		if (mBlinkTime > 0)
		{
			mBlinkTime -= deltaTime; //Gradially reduce blink time
			mBlinkTime = mBlinkTime > 0 ? mBlinkTime : 0.f;

			GetSprite().setColor(LerpColor(sf::Color::White, mBlinkColorOffset, mBlinkTime));
		}
	}
}