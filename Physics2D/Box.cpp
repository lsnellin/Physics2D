#include "Box.h"

using namespace Physics2D;
using sf::Vector2f;

Box::Box() :
	size(Vector2f()),
	rigidbody(),
	halfSize(size / 2.0f)
{
}

Box::Box(Vector2f min, Vector2f max) :
	size(max - min),
	rigidbody(),
	halfSize(size / 2.0f)
{
	rigidbody.setPosition(min + halfSize);
}

Vector2f Box::getMin() {
	return this->rigidbody.getPosition() - this->halfSize;
}

Vector2f Box::getMax() {
	return this->rigidbody.getPosition() + this->halfSize;
}

void Box::rotate(float rotation) {
	rigidbody.setRotation(
		this->getRigidbody().getRotation() + rotation
	);
}

std::vector<Vector2f> Box::getVertices() {
	std::vector<Vector2f> vertices;

	vertices.push_back(Vector2f(this->getMin()));
	vertices.push_back(Vector2f(this->getMin().x, this->getMax().y));
	vertices.push_back(Vector2f(this->getMax().x, this->getMin().y));
	vertices.push_back(Vector2f(this->getMax()));

	//TODO: Implement rotating the vertices if the box is rotated
	for (auto& vertex : vertices) {
		rotateVector2f(&vertex, this->getRigidbody().getRotation(), this->getRigidbody().getPosition());

	}

	return vertices;
}

Rigidbody2D Box::getRigidbody() {
	return this->rigidbody;
}
