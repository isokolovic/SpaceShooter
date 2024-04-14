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
				Render();
			}
		}
	}
	void Application::Tick(float deltaTime)
	{
		std::cout << "Ticking at frame rate: " << 1.f / deltaTime << std::endl;
	}
	void Application::Render()
	{
		mWindow.clear();

		sf::RectangleShape rect{ sf::Vector2f{100, 100} };
		rect.setFillColor(sf::Color::Green);
		rect.setOrigin(50, 50);
		rect.setPosition(mWindow.getSize().x / 2.f, mWindow.getSize().y / 2.f);

		mWindow.draw(rect);
		mWindow.display();
	}
}
