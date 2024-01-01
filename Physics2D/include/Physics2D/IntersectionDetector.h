#pragma once

#include <SFML/Graphics.hpp>
#include "Circle.h"
#include "AABB.h"
#include "Box.h"
#include "pUtil.h"
#include <cmath>

namespace Physics2D {
	bool pointInCirlce(sf::Vector2f point, Physics2D::Circle circle);
	bool pointInAABB(sf::Vector2f point, Physics2D::AABB aabb);
	bool pointInBox(sf::Vector2f point, Physics2D::Box box);
}

