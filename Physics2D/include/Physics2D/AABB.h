#pragma once
#include <SFML/Graphics.hpp>
#include "Rigidbody2D.h"
#include "PhysicsObject.h"

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
		std::vector<sf::Vector2f> getVertices();
		void setRigidbody(Physics2D::Rigidbody2D);
		void setSize(sf::Vector2f size);
	};
}