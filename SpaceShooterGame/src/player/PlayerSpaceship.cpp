#include "player/PlayerSpaceship.h"
#include "SFML/System.hpp"
#include "framework/MathUtility.h"
#include "weapon/BulletShooter.h"
#include "weapon/FrontalWiper.h"
#include "weapon/ThreeWayShooter.h"

namespace ss {

	PlayerSpaceship::PlayerSpaceship(World* owningWorld, const std::string& path)
		: Spaceship{ owningWorld, path },
		mMoveInput{},
		mSpeed{ 200.f },
		mShooter{ new ThreeWayShooter{ this, 1.f, {50.f, 0.f} } },
		mInvunerableTime{ 2.f },
		mInvunerable{ true },
		mInvunerableFlashInterval{ 0.5f },
		mInvunerableFlashTimer{ 0.f },
		mInvunerableFlashDir{ 1 }
	{
		SetTeamID(1);
		mShooter->SetCurrentLevel(4);
	}

	void PlayerSpaceship::Tick(float deltaTime)
	{
		Spaceship::Tick(deltaTime);
		HandleInput();
		ConsumeInput(deltaTime);
		UpdateInvunerable(deltaTime);
	}

	void PlayerSpaceship::Shoot()
	{
		if (mShooter)
		{
			mShooter->Shoot();
		}
	}

	void PlayerSpaceship::SetShooter(unique<Shooter>&& newShooter)
	{
		if (mShooter && typeid(*mShooter.get()) == typeid(*newShooter.get()))
		{
			mShooter->IncrementLevel();
			return;
		}

		mShooter = std::move(newShooter);
	}

	void PlayerSpaceship::ApplyDamage(float amt)
	{
		if (!mInvunerable)
		{
			Spaceship::ApplyDamage(amt);
		}
	}

	void PlayerSpaceship::BeginPlay()
	{
		Spaceship::BeginPlay();
		TimerManager::Get().SetTimer(GetWeakRef(), &PlayerSpaceship::StopInvunerable, mInvunerableTime);
	}

	void PlayerSpaceship::HandleInput()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			mMoveInput.y = -1.f;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			mMoveInput.y = 1.f;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			mMoveInput.x = -1.f;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			mMoveInput.x = 1.f;
		}

		ClampInputOnEdge();
		NormalizeInput();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			Shoot();
		}
	}

	void PlayerSpaceship::NormalizeInput()
	{
		Normalize(mMoveInput);
	}

	void PlayerSpaceship::ClampInputOnEdge()
	{
		sf::Vector2f actorLocation = GetActorLocation();

		if (actorLocation.x < 0 && mMoveInput.x == -1)
		{
			mMoveInput.x = 0.f; //0.f = not being able to move
		}

		if (actorLocation.x > GetWindowSize().x && mMoveInput.x == 1.f)
		{
			mMoveInput.x = 0.f;
		}

		if (actorLocation.y < 0 && mMoveInput.y == -1)
		{
			mMoveInput.y = 0.f;
		}

		if (actorLocation.y > GetWindowSize().y && mMoveInput.y == 1.f)
		{
			mMoveInput.y = 0.f;
		}
	}

	void PlayerSpaceship::ConsumeInput(float deltaTime)
	{
		SetVelocity(mMoveInput * mSpeed);
		mMoveInput.x = mMoveInput.y = 0;
	}

	void PlayerSpaceship::StopInvunerable()
	{
		GetSprite().setColor({ 255, 255, 255, 255 });
		mInvunerable = false;
	}

	void PlayerSpaceship::UpdateInvunerable(float deltaTime)
	{
		if (!mInvunerable) return;

		mInvunerableFlashTimer += deltaTime * mInvunerableFlashDir;
		if (mInvunerableFlashTimer < 0 || mInvunerableFlashTimer > mInvunerableFlashInterval)
		{
			mInvunerableFlashDir += -1;
		}

		GetSprite().setColor(LerpColor({ 255,255,255,64 }, { 255,255,255,128 }, mInvunerableFlashTimer / mInvunerableFlashInterval));
	}
}