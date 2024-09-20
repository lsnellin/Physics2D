#pragma once
#include <SFML/Graphics.hpp>
#include "PhysicsObject.h"
#include "Rigidbody2D.h"
#include "AABB.h"

namespace Physics2D {
	class Circle: public sf::CircleShape, public Physics2D::Collider2D, public Physics2D::PhysicsObject
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
		void setCenter(sf::Vector2f center);
		void setRadius(float radius);
		void setRigidbody(Physics2D::Rigidbody2D* rigidbody);

		virtual Physics2D::Type getType() override;
		virtual void updateFromRigidbody() override;
		virtual Physics2D::Rigidbody2D* getRigidbody() override;
	};
}


