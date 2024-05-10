#include "widgets/MainMenuHUD.h"

namespace ss
{
	MainMenuHUD::MainMenuHUD()
		: mTitleText{ "Space Shooter" },
		mStartButton{ "Start" },
		mQuitButton{ "Quit" }
	{
		mTitleText.SetTextSize(20);
		mStartButton.SetTextSize(15);
		mQuitButton.SetTextSize(15);
	}

	void MainMenuHUD::Draw(sf::RenderWindow& windowRef)
	{
		mTitleText.NativeDraw(windowRef);
		mStartButton.NativeDraw(windowRef);
		mQuitButton.NativeDraw(windowRef);
	}

	bool MainMenuHUD::HandleEvent(const sf::Event& event)
	{
		return mStartButton.HandleEvent(event) || mQuitButton.HandleEvent(event) || HUD::HandleEvent(event);
	}

	void MainMenuHUD::Init(const sf::RenderWindow& windowRef)
	{
		sf::Vector2u windowSize = windowRef.getSize();
		mTitleText.SetWidgetLocation({ windowSize.x / 2.f - mTitleText.GetBound().width / 2.f, 100.f });

		mStartButton.SetWidgetLocation({ windowSize.x / 2.f - mStartButton.GetBound().width / 2.f, windowSize.y / 2.f });
		mQuitButton.SetWidgetLocation(mStartButton.GetWidgetLocation() + sf::Vector2f{ 0.f, 50.f });

		mStartButton.onButtonClicked.BindAction(GetWeakRef(), &MainMenuHUD::StartButtonClicked);
		mQuitButton.onButtonClicked.BindAction(GetWeakRef(), &MainMenuHUD::QuitButtonClicked);
	}

	void MainMenuHUD::StartButtonClicked()
	{
		onStartButtonClicked.Broadcast();
	}

	void MainMenuHUD::QuitButtonClicked()
	{
		onQuitButtonClicked.Broadcast();
	}
}