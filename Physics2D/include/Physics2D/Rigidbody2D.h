#pragma once
#include <SFML/Graphics.hpp>

namespace Physics2D {
	class Rigidbody2D {
	private:
		sf::Vector2f position;
		float rotation;

	public:
		Rigidbody2D();
		Rigidbody2D(sf::Vector2f position, float rotation);
		sf::Vector2f getPosition();
		float getRotation();
		void setPosition(sf::Vector2f);
		void setRotation(float rotation);
	};
}