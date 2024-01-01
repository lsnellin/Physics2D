#include "AABB.h"

using namespace Physics2D;
using namespace sf;

AABB::AABB():
size(Vector2f()), 
rigidbody(), 
halfSize(size / 2.0f)
{
}

AABB::AABB(Vector2f min, Vector2f max):
size(max - min), 
rigidbody(), 
halfSize(size / 2.0f)
{
	this->getRigidbody().setPosition(min + halfSize);
}

Rigidbody2D AABB::getRigidbody() {
	return this->rigidbody;
}

Vector2f AABB::getMin() {
	return this->rigidbody.getPosition() - this->halfSize;
}

Vector2f AABB::getMax() {
	return this->rigidbody.getPosition() + this->halfSize;
}
