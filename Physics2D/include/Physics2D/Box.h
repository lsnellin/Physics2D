#pragma once

#include <SFML/Graphics.hpp>
#include "Rigidbody2D.h"
#include "pUtil.h"

namespace Physics2D {
	class Box
	{
	private:
		sf::Vector2f size;
		sf::Vector2f halfSize;
		Rigidbody2D rigidbody;
	public:
		Box();
		Box(sf::Vector2f min, sf::Vector2f max);
		sf::Vector2f getMin();
		sf::Vector2f getMax();
		sf::Vector2f getHalfsize();
		void rotate(float rotation);
		std::vector<sf::Vector2f> getVertices();
		Physics2D::Rigidbody2D getRigidbody();
		void setCenter(sf::Vector2f position);
	};
}

