#pragma once
#include <SFML/Graphics.hpp>
#include "Rigidbody2D.h"
#include "PhysicsObject.h"

namespace Physics2D {
	class Circle: public sf::CircleShape, PhysicsObject
	{
	private:
		float radius;
		Rigidbody2D rigidbody;

	public:
		Circle();
		Circle(float radius, sf::Vector2f center);
		float getRadius();
		sf::Vector2f getCenter();
		Physics2D::Rigidbody2D* getRigidbody();
		void setCenter(sf::Vector2f center);
		void setRadius(float radius);
		void setRigidbody(Physics2D::Rigidbody2D);
		void updateFromRigidbody();
	};
}


