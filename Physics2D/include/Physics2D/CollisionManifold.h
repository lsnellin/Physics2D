#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "pUtil.h"

namespace Physics2D {
	class CollisionManifold {
	private:
		sf::Vector2f normal;
		std::vector<sf::Vector2f> contactPoints;
		float depth;
		bool isColliding;
	public:
		CollisionManifold();
		CollisionManifold(sf::Vector2f normal, float depth);
		void addContactPoint(sf::Vector2f point);
		void rotate(float r, sf::Vector2f origin);
		void setNormal(sf::Vector2f normal);
		void setDepth(float depth);
		sf::Vector2f getNormal();
		std::vector<sf::Vector2f> getContactPoints();
		float getDepth();
		bool getColliding();
	};
}