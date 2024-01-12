#pragma once
#include <SFML/Graphics.hpp>
#include "Rigidbody2D.h"

namespace Physics2D {
	class Circle
	{
	private:
		float radius;
		Rigidbody2D rigidbody;

	public:
		Circle();
		Circle(float radius, sf::Vector2f center);
		float getRadius();
		sf::Vector2f getCenter();
		void setCenter(sf::Vector2f center);
		void setRadius(float radius);
	};
}


