#pragma once

#include <SFML/Graphics.hpp>
#include "Rigidbody2D.h"
#include "pUtil.h"
#include "PhysicsObject.h"

namespace Physics2D {
	class Box: public sf::RectangleShape, PhysicsObject
	{
	private:
		sf::Vector2f size;
		sf::Vector2f halfSize;
		Rigidbody2D rigidbody;
	public:
		Box();
		Box(sf::Vector2f min, sf::Vector2f max);
		sf::Vector2f getLocalMin();
		sf::Vector2f getLocalMax();
		sf::Vector2f getHalfsize();
		void rotate(float rotation);
		std::vector<sf::Vector2f> getVertices();
		Physics2D::Rigidbody2D* getRigidbody();
		void setCenter(sf::Vector2f position);
		void setRigidbody(Physics2D::Rigidbody2D);
		void setSize(sf::Vector2f size);
		void updateFromRigidbody();
	};
}

