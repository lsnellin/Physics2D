#include "Circle.h"

using namespace Physics2D;
using namespace sf;

Circle::Circle() :
	Circle(1.0f)
{
}

Circle::Circle(float radius) :
	rigidbody(),
	radius(radius)
{
}

float Circle::getRadius() {
	return this->radius;
}

Vector2f Circle::getCenter() {
	return this->rigidbody.getPosition();
}
