#include "Circle.h"

using namespace Physics2D;
using sf::Vector2f;

Circle::Circle() :
	Circle(1.0f, sf::Vector2f(0,0))
{
}

Circle::Circle(float radius, Vector2f center) :
	rigidbody(),
	radius(radius)
{
	rigidbody.setPosition(center);
}

float Circle::getRadius() {
	return this->radius;
}

Vector2f Circle::getCenter() {
	return this->rigidbody.getPosition();
}

void Circle::setCenter(Vector2f center) {
	this->rigidbody.setPosition(center);
}

void Circle::setRadius(float radius) {
	this->radius = radius;
}
