#include "framework/Application.h"

namespace ly{
	Application::Application()
		: mWindow{ sf::VideoMode(600, 800), "Space Shooter" }
	{


	}
	void Application::Run()
	{
		//If Event is close, close the window
		while (mWindow.isOpen()) {
			sf::Event windowEvent;
			while (mWindow.pollEvent(windowEvent)) {
				if (windowEvent.type == sf::Event::EventType::Closed()) {
					mWindow.close();
				}
			}
		}
	}
}
