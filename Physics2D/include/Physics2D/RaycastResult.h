#pragma once
#include <SFML/Graphics.hpp>

namespace Physics2D {
	class RaycastResult {
	private:
		sf::Vector2f point; //Point hit
		sf::Vector2f normal; //Direction that the ray "bounces"
		float t; //Distance from origin to point
		bool hit; //Whether or not the raycast succeeded

	public:
		RaycastResult();
		void init(sf::Vector2f point, sf::Vector2f normal, float t, bool hit);
		static void reset(Physics2D::RaycastResult& result);
		sf::Vector2f getPoint();
		sf::Vector2f getNormal();
		float getT();
	};
}