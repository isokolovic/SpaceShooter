#include "framework/Application.h"
#include <iostream>

namespace ly{
	Application::Application()
		: mWindow{ sf::VideoMode(600, 800), "Space Shooter" }, 
		mTargetFrameRate{60.f},
		mTickClock{}
	{

	}
	void Application::Run()
	{
		mTickClock.restart();
		float accumulatedTime = 0.f;
		float targetDeltaTime = 1.f / mTargetFrameRate;

		//If Event is close, close the window
		while (mWindow.isOpen()) {
			sf::Event windowEvent;
			while (mWindow.pollEvent(windowEvent)) {
				if (windowEvent.type == sf::Event::EventType::Closed()) {
					mWindow.close();
				}
			}

			accumulatedTime += mTickClock.restart().asSeconds();
			while (accumulatedTime > targetDeltaTime)
			{
				accumulatedTime -= targetDeltaTime;
				Tick(targetDeltaTime);
			}
		}
	}
	void Application::Tick(float deltaTime)
	{
		std::cout << "Ticking at frame rate: " << 1.f / deltaTime << std::endl;
	}
	void Application::Render()
	{
	}
}
