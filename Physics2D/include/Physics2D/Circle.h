#pragma once
#include <SFML/Graphics.hpp>
#include "Rigidbody2D.h"

namespace Physics2D {
	class Circle: public sf::CircleShape, public Physics2D::Collider2D
	{
	private:
		float radius;
		Physics2D::Rigidbody2D* rigidbody;

	public:
		Circle();
		Circle(float radius, sf::Vector2f center);
		~Circle();
		float getRadius();
		sf::Vector2f getCenter();
		Physics2D::Rigidbody2D* getRigidbody();
		virtual Physics2D::Type getType() override;
		void setCenter(sf::Vector2f center);
		void setRadius(float radius);
		void setRigidbody(Physics2D::Rigidbody2D* rigidbody);
		void updateFromRigidbody();
	};
}


