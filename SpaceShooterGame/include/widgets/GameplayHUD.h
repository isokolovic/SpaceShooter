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

		void GameFinished(bool playerWon);
		virtual void Draw(sf::RenderWindow& windowRef) override;
		virtual void Tick(float deltaTime) override;
		virtual bool HandleEvent(const sf::Event& event) override;
		Delegate<> onRestartButtonClicked;
		Delegate<> onQuitButtonClicked;
	private:
		void PlayerHealthUpdated(float amt, float currentHealth, float maxHealth);
		void PlayerLifeCountUpdated(int amt);
		void PlayerScoreUpdated(int amt);
		void PlayerSpaceshipDestroyed(Actor* actor);
		void RefreshHealthBar();
		void ConnectPlayerStatus();
		void RestartButtonClicked();
		void QuitButtonClicked();
		virtual void Init(const sf::RenderWindow& windowRef) override;

		TextWidget mFrameRateText;
		ValueGauge mPlayerHealthBar;
		ImageWidget mPlayerLifeIcon;
		TextWidget mPlayerLifeText;
		ImageWidget mPlayerScoreIcon;
		TextWidget mPlayerScoreText;

		sf::Color mHealthyHealthBarColor;
		sf::Color mCriticalHealthBarColor;
		float mCriticalThreshold;

		float mWidgetSpacing;

		TextWidget mWinLoseText;
		TextWidget mFinalScoreText;
		Button mRestartButton;
		Button mQuitButton;

		sf::Vector2u mWindowSize;
	};
}