#include "widgets/GameplayHUD.h"

namespace ss
{
	GameplayHUD::GameplayHUD()
		:mFrameRateText{ "Frame Rate:" }
	{
		mFrameRateText.SetTextSize(20);
	}

	void GameplayHUD::Draw(sf::RenderWindow& windowRef)
	{
		mFrameRateText.NativeDraw(windowRef);
	}

	void GameplayHUD::Tick(float deltaTime)
	{
		int frameRate = int(1 / deltaTime);
		std::string frameRateText = "Frame rate: " + std::to_string(frameRate);
		mFrameRateText.SetString(frameRateText);
	}
}