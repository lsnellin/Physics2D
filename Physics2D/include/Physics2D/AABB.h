#pragma once
#include <SFML/Graphics.hpp>
#include "Rigidbody2D.h"

namespace Physics2D{
	class AABB : public Physics2D::Collider2D, public sf::RectangleShape
	{
	private:
		sf::Vector2f size;
		sf::Vector2f halfSize;
		Rigidbody2D* rigidbody;
	public:
		AABB();
		AABB(sf::Vector2f min, sf::Vector2f max);
		~AABB();
		Physics2D::Rigidbody2D* getRigidbody();
		sf::Vector2f getMin();
		sf::Vector2f getMax();
		std::vector<sf::Vector2f> getVertices();
		Type getType();
		void setCenter(sf::Vector2f position);
		void setRigidbody(Physics2D::Rigidbody2D* rigidbody);
		void setSize(sf::Vector2f size);
		void updateFromRigidbody();
	};
}