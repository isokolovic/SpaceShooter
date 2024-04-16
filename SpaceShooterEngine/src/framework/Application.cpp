#include "framework/Application.h"
#include "framework/Core.h"
#include "framework/World.h"

namespace ss{

	Application::Application(unsigned int windowWidth, unsigned int windowHeight, const std::string& title, sf::Uint32 style)
		: mWindow{ sf::VideoMode(windowWidth, windowHeight), title, style },
		mTargetFrameRate{ 60.f },
		mTickClock{},
		currentWorld{ nullptr }
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

			float frameDeltaTime = mTickClock.restart().asSeconds();
			accumulatedTime += frameDeltaTime;

			while (accumulatedTime > targetDeltaTime)
			{
				accumulatedTime -= targetDeltaTime;
				TickInternal(targetDeltaTime);
				RenderInternal();
			}
		}
	}

	void Application::TickInternal(float deltaTime)
	{
		//Execute Tick on the top level first then TickInternal of the currentWorld
		//First tick if player input, after what game logic is updated
		Tick(deltaTime);

		if (currentWorld) {
			//currentWorld->BeginPlayInternal(); //Transfered to be calleed only at the begining (LoadWorld()). May not work when changing level?
			currentWorld->TickInternal(deltaTime);
		}
	}

	void Application::RenderInternal()
	{
		mWindow.clear();

		Render();

		mWindow.display();
	}

	void Application::Render()
	{
		sf::RectangleShape rect{ sf::Vector2f{100, 100} };
		rect.setFillColor(sf::Color::Green);
		rect.setOrigin(50, 50);
		rect.setPosition(mWindow.getSize().x / 2.f, mWindow.getSize().y / 2.f);

		mWindow.draw(rect);
	}

	void Application::Tick(float deltaTime)
	{
	}
}
