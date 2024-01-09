#pragma once
#include <SFML/Graphics.hpp>
#include "pUtil.h""

namespace Physics2D {
	class Ray {
	private:
		sf::Vector2f origin;
		sf::Vector2f direction;

	public:
		Ray(sf::Vector2f origin, sf::Vector2f direction);
		sf::Vector2f getOrigin();
		sf::Vector2f getDirection();
		void rotate(float angle, sf::Vector2f origin);
	};
}