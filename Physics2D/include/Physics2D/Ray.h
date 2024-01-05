#pragma once
#include <SFML/Graphics.hpp>

namespace Physics2D {
	class Ray {
	private:
		sf::Vector2f origin;
		sf::Vector2f direction;

	public:
		Ray(sf::Vector2f origin, sf::Vector2f direction);
		sf::Vector2f getOrigin();
		sf::Vector2f getDirection();
	};
}