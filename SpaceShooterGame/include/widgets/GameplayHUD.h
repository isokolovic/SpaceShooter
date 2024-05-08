#pragma once
#include "widgets/ButtonWidget.h"
#include "widgets/HUD.h"
#include "widgets/ImageWidget.h"
#include "widgets/TextWidget.h"
#include "widgets/ValueGauge.h"

namespace ss
{
	class Actor;

	class GameplayHUD : public HUD
	{
	public:
		GameplayHUD();
		virtual void Draw(sf::RenderWindow& windowRef) override;
		virtual void Tick(float deltaTime) override;

	private:
		virtual void Init(const sf::RenderWindow& windowRef) override;
		void PlayerHealthUpdated(float amt, float currentHealth, float maxHealth);
		void PlayerLifeCountUpdated(int amt);
		void PlayerScoreUpdated(int amt);
		void PlayerSpaceshipDestroyed(Actor* actor);
		void RefreshHealthBar();
		void ConnectPlayerStatus();

		TextWidget mFrameRateText;
		ValueGauge mPlayerHealthBar;
		ImageWidget mPlayerLifeIcon;
		TextWidget mPlayerLifeText;
		ImageWidget mPlayerScoreIcon;
		TextWidget mPlayerScoreText;

		//TODO Remove
		Button TestButton;

		sf::Color mHealthyHealthBarColor;
		sf::Color mCriticalHealthBarColor;
		float mCriticalThreshold;

		float mWidgetSpacing;
	};
}