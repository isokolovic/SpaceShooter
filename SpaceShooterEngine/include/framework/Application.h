#pragma once
#include "SFML/Graphics.hpp"
#include "framework/Core.h"

namespace ss {

	class World;

	class Application {

	public:
		Application();
		void Run();

		template<typename WorldType>
		weak<WorldType> LoadWorld();

	private:
		void TickInternal(float deltaTime);
		void RenderInternal();

		virtual void Render();
		virtual void Tick(float deltaTime);

		sf::RenderWindow mWindow;
		float mTargetFrameRate;
		sf::Clock mTickClock;

		shared<World> currentWorld;
	};

	//Template function cannot be in .cpp file
	template<typename WorldType>
	weak<WorldType> Application::LoadWorld(){

		//currentWorld represents a base class. 
		//Returning a newWorld since type must be complied. Also, child type cannot hold a base type. 
		shared<WorldType> newWorld{ new WorldType{this} };
		currentWorld = newWorld;
		currentWorld->BeginPlayInternal();
		return newWorld;
	}
}