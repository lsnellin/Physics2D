#pragma once
#include <SFML/Graphics.hpp>
#include "Rigidbody2D.h"

namespace Physics2D {
	class AABB
	{
	private:
		sf::Vector2f size;
		sf::Vector2f halfSize;
		Rigidbody2D rigidbody;
	public:
		AABB();
		AABB(sf::Vector2f min, sf::Vector2f max);
		Physics2D::Rigidbody2D getRigidbody();
		sf::Vector2f getMin();
		sf::Vector2f getMax();
	};
}