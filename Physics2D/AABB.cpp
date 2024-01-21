#include "AABB.h"

using namespace Physics2D;
using namespace sf;

AABB::AABB():
size(Vector2f()), 
halfSize(size / 2.0f),
rigidbody()
{
}

AABB::AABB(Vector2f min, Vector2f max) :
	size(max - min),
	halfSize(size / 2.0f),
	rigidbody(min + halfSize, 0.f)
{
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

std::vector<Vector2f> AABB::getVertices() {
	std::vector<Vector2f> vertices;

	vertices.push_back(Vector2f(this->getMin()));
	vertices.push_back(Vector2f(this->getMin().x, this->getMax().y));
	vertices.push_back(Vector2f(this->getMax().x, this->getMin().y));
	vertices.push_back(Vector2f(this->getMax()));

	return vertices;
}

void AABB::setRigidbody(Rigidbody2D rigidbody) {
	this->rigidbody = rigidbody;
}

void AABB::setSize(Vector2f size) {
	this->size = size;
	this->halfSize = size / 2.f;
}
