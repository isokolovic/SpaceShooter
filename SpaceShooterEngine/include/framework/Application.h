#pragma once
#include "SFML/Graphics.hpp"
#include "framework/Core.h"

namespace ss
{
	class World;

	class Application
	{

	public:
		Application(unsigned int windowWidth, unsigned int windowHeight, const std::string& title, sf::Uint32 style);
		void Run();

		template<typename WorldType>
		weak<WorldType> LoadWorld();

		sf::Vector2u GetWindowSize() const;
		sf::RenderWindow& GetWindow() { return mWindow; }
		const sf::RenderWindow& GetWindow() const { return mWindow; }

	private:
		void DispatchEvent(const sf::Event& event);
		void TickInternal(float deltaTime);
		void RenderInternal();

		virtual void Render();
		virtual void Tick(float deltaTime);

		sf::RenderWindow mWindow;
		float mTargetFrameRate;
		sf::Clock mTickClock;

		shared<World> mCurrentWorld;

		sf::Clock mCleanCycleClock;
		float mCleanCycleInterval;
	};

	//Template function cannot be in .cpp file
	template<typename WorldType>
	weak<WorldType> Application::LoadWorld()
	{
		//currentWorld represents a base class. 
		//Returning a newWorld since type must be complied. Also, child type cannot hold a base type. 
		shared<WorldType> newWorld{ new WorldType{this} };
		mCurrentWorld = newWorld;
		mCurrentWorld->BeginPlayInternal();
		return newWorld;
	}
}