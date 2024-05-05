#include "widgets/HUD.h"

namespace ss
{
	HUD::HUD()
		: mAlreadyInit{ false }
	{
	}

	void HUD::Init(const sf::RenderWindow& windowRef)
	{
	}

	void HUD::NativeInit(const sf::RenderWindow& windowRef)
	{
		if (!mAlreadyInit)
		{
			mAlreadyInit = true;
			Init(windowRef);
		}
	}

	bool HUD::HandleEvent(const sf::Event& event)
	{
		return false;
	}

	void HUD::Tick(float deltaTime)
	{
	}
}