#include "Ray.h"

using namespace Physics2D;
using sf::Vector2f;

Ray::Ray(Vector2f origin, Vector2f direction) :
	origin(origin),
	direction(direction)
{
}

Vector2f Ray::getOrigin() {
	return this->origin;
}

Vector2f Ray::getDirection() {
	return this->direction;
}

void Ray::rotate(float angle, Vector2f center) {
	Vector2f origin = this->origin;
	Vector2f direction = this->direction;

	rotateVector2f(&origin, angle, center);
	rotateVector2f(&direction, angle, Vector2f(0.f,0.f));

	this->origin = origin;
	this->direction = direction;
}