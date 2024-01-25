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
	//Point vs Primitive:
	bool pointOnLine(sf::Vector2f point, Physics2D::Line& line);
	bool pointInCircle(sf::Vector2f point, Physics2D::Circle& circle);
	bool pointInAABB(sf::Vector2f point, Physics2D::AABB& aabb);
	bool pointInBox(sf::Vector2f point, Physics2D::Box& box);

	//Line vs Primitive:
	bool lineVSCircle(Physics2D::Line& line, Physics2D::Circle& circle);
	bool lineVSAABB(Physics2D::Line& line, Physics2D::AABB& aabb);
	bool lineVSBox(Physics2D::Line& line, Physics2D::Box& box);
	bool raycast(Physics2D::Circle& circle, Physics2D::Ray ray, Physics2D::RaycastResult& result);
	bool raycast(Physics2D::AABB& aabb, Physics2D::Ray ray, Physics2D::RaycastResult& result);
	bool raycast(Physics2D::Box& box, Physics2D::Ray ray, Physics2D::RaycastResult& result);

	//Circle vs Primitive:
	bool circleVSLine(Physics2D::Circle& circle, Physics2D::Line& line);
	bool circleVSCircle(Physics2D::Circle& circle1, Physics2D::Circle& circle2);
	bool circleVSAABB(Physics2D::Circle& circle, Physics2D::AABB& aabb);
	bool circleVSBox(Physics2D::Circle& circle, Physics2D::Box& box);

	//AABB vs Primitive:
	bool aabbVSLine(Physics2D::AABB& aabb, Physics2D::Line& line);
	bool aabbVSCircle(Physics2D::AABB& aabb, Physics2D::Circle& circle);
	bool aabbVSAABB(Physics2D::AABB& aabb1, Physics2D::AABB& aabb2);
	bool aabbVSBox(Physics2D::AABB& aabb, Physics2D::Box& box);

	//Box vs Primitive:
	bool boxVSLine(Physics2D::Box& box, Physics2D::Line& line);
	bool boxVSCircle(Physics2D::Box& box, Physics2D::Circle& circle);
	bool boxVSAABB(Physics2D::Box& box, Physics2D::AABB& aabb);
	bool boxVSBox(Physics2D::Box& box1, Physics2D::Box& box2);

	//Separating Axis Theorem Helpers
	bool overlapOnAxis(Physics2D::AABB& aabb1, Physics2D::AABB& aabb2, sf::Vector2f axis);
	bool overlapOnAxis(Physics2D::AABB& aabb, Physics2D::Box& box, sf::Vector2f axis);
	bool overlapOnAxis(Physics2D::Box& box1, Physics2D::Box& box2, sf::Vector2f axis);
	sf::Vector2f getInterval(Physics2D::AABB& aabb, sf::Vector2f axis);
	sf::Vector2f getInterval(Physics2D::Box& box, sf::Vector2f axis);

}

