#pragma once
#include "widgets/HUD.h"
#include "widgets/TextWidget.h"
#include "widgets/ValueGauge.h"

namespace ss
{

	class GameplayHUD : public HUD
	{
	public:
		GameplayHUD();
		virtual void Draw(sf::RenderWindow& windowRef) override;
		virtual void Tick(float deltaTime) override;
	private:
		virtual void Init(const sf::RenderWindow& windowRef) override;
		TextWidget mFrameRateText;
		ValueGauge mPlayerHealthBar;
	};
}