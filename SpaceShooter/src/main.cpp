#include <iostream>
#include <SFML/Graphics.hpp>

int main() {
	sf::RenderWindow renderWindow{ sf::VideoMode(100, 100), "MyWindow" };

	//If Event is close, close the window
	while(renderWindow.isOpen()) {
		sf::Event windowEvent;
		while (renderWindow.pollEvent(windowEvent)) {
			if (windowEvent.type == sf::Event::EventType::Closed()) {
				renderWindow.close();
			}
		}
	}

	std::cout << "Hello world! " << std::endl;
}