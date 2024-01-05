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