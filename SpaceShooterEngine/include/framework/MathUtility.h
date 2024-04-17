#pragma once
#include <SFML/Graphics.hpp>

namespace ss {

	sf::Vector2f RotationToVector(float rotation);
	float DegreesToRatians(float degrees);
	float RadiansToDegrees(float radians);
}