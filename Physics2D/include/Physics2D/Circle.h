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
		Circle(float radius);
		float getRadius();
		sf::Vector2f getCenter();
	};
}


