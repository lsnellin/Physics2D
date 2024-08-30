#include "AABB.h"

using namespace Physics2D;
using namespace sf;

AABB::AABB():
size(Vector2f()), 
halfSize(size / 2.0f),
rigidbody(new Rigidbody2D(this))
{
}

AABB::AABB(Vector2f min, Vector2f max) :
	size(max - min),
	halfSize(size / 2.f),
	rigidbody(new Rigidbody2D(min + halfSize, 0.f, this))
{
	RectangleShape::setOrigin(min + halfSize);
	RectangleShape::setSize(size);
}

AABB::~AABB() {
	delete rigidbody;
}

Rigidbody2D* AABB::getRigidbody() {
	return this->rigidbody;
}

Vector2f AABB::getMin() {
	return this->rigidbody->getPosition() - this->halfSize;
}

Vector2f AABB::getMax() {
	return this->rigidbody->getPosition() + this->halfSize;
}

std::vector<Vector2f> AABB::getVertices() {
	std::vector<Vector2f> vertices;

	vertices.push_back(Vector2f(this->getMin()));
	vertices.push_back(Vector2f(this->getMin().x, this->getMax().y));
	vertices.push_back(Vector2f(this->getMax().x, this->getMin().y));
	vertices.push_back(Vector2f(this->getMax()));

	return vertices;
}

Type AABB::getType() {
	return Type::AABB;
}

Vector2f AABB::getCenter() {
	return this->rigidbody->getPosition();
}

void AABB::setRigidbody(Rigidbody2D* rigidbody) {
	this->rigidbody = rigidbody;
}

void AABB::setSize(Vector2f size) {
	this->size = size;
	this->halfSize = size / 2.f;
	RectangleShape::setSize(size);
}

void AABB::setCenter(Vector2f center) {
	this->rigidbody->setPosition(center);
	RectangleShape::setPosition(center);
}

void AABB::updateFromRigidbody() {
	RectangleShape::setPosition(rigidbody->getPosition());
}

bool AABB::contains(AABB ab) {
	Vector2f minContainer = this->getMin();
	Vector2f maxContainer = this->getMax();

	Vector2f minObject = ab.getMin();
	Vector2f maxObject = ab.getMax();

	return (minContainer.x <= minObject.x) && (minContainer.y <= minObject.y) && (maxContainer.x >= maxObject.x) && (maxContainer.y >= maxObject.y);
}
