#pragma once
#include <SFML/Graphics.hpp>
#include "PhysicsObject.h"
#include "Rigidbody2D.h"

namespace Physics2D{
	class AABB : public Physics2D::Collider2D, public sf::RectangleShape, public Physics2D::PhysicsObject
	{
	private:
		sf::Vector2f size;
		sf::Vector2f halfSize;
		Rigidbody2D* rigidbody;
	public:
		AABB();
		AABB(sf::Vector2f min, sf::Vector2f max);
		~AABB();
		
		sf::Vector2f getMin();
		sf::Vector2f getMax();
		sf::Vector2f getCenter();
		std::vector<sf::Vector2f> getVertices();
		void setCenter(sf::Vector2f position);
		void setRigidbody(Physics2D::Rigidbody2D* rigidbody);
		void setSize(sf::Vector2f size);
		bool contains(Physics2D::AABB ab);

		virtual Physics2D::Type getType() override;
		virtual void updateFromRigidbody() override;
		virtual Physics2D::Rigidbody2D* getRigidbody() override;
	};
}