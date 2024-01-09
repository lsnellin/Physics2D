#pragma once

#include <SFML/Graphics.hpp>
#include "Circle.h"
#include "AABB.h"
#include "Box.h"
#include "Line.h"
#include "pUtil.h"
#include "Ray.h"
#include "RaycastResult.h"
#include <cmath>

namespace Physics2D {
	bool pointOnLine(sf::Vector2f point, Physics2D::Line line);
	bool pointInCircle(sf::Vector2f point, Physics2D::Circle circle);
	bool pointInAABB(sf::Vector2f point, Physics2D::AABB aabb);
	bool pointInBox(sf::Vector2f point, Physics2D::Box box);
	bool lineVSCircle(Physics2D::Line line, Physics2D::Circle circle);
	bool lineVSAABB(Physics2D::Line line, Physics2D::AABB aabb);
	bool lineVSBox(Physics2D::Line line, Physics2D::Box box);
	bool raycast(Physics2D::Circle circle, Physics2D::Ray ray, Physics2D::RaycastResult* result);
	bool raycast(Physics2D::AABB aabb, Physics2D::Ray ray, Physics2D::RaycastResult* result);
	bool raycast(Physics2D::Box box, Physics2D::Ray ray, Physics2D::RaycastResult* result);
}

