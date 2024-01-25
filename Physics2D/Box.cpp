#include "Box.h"

using namespace Physics2D;
using sf::Vector2f;

Box::Box() :
	size(Vector2f()),
	rigidbody(new Rigidbody2D(this)),
	halfSize(size / 2.0f)
{
}

Box::Box(Vector2f min, Vector2f max) :
	size(max - min),
	rigidbody(new Rigidbody2D(min + size / 2.0f, 0.f, this)),
	halfSize(size / 2.0f)
{
	setSize(max - min);
	setCenter(min + halfSize);
}

Box::~Box() {
	delete rigidbody;
}

void Box::setCenter(Vector2f center) {
	this->rigidbody->setPosition(center);
	RectangleShape::setPosition(center);
}

Vector2f Box::getLocalMin() {
	return this->rigidbody->getPosition() - this->halfSize;
}

Vector2f Box::getLocalMax() {
	return this->rigidbody->getPosition() + this->halfSize;
}

Vector2f Box::getHalfsize() {
	return this->halfSize;
}

void Box::rotate(float rotation) {
	float newRotation = rigidbody->getRotation() + rotation;
	newRotation -= ((int)newRotation / 360) * 360;
	rigidbody->setRotation(newRotation);
	RectangleShape::rotate(rotation);
}

std::vector<Vector2f> Box::getVertices() {
	std::vector<Vector2f> vertices;

	vertices.push_back(Vector2f(this->getLocalMin()));
	vertices.push_back(Vector2f(this->getLocalMin().x, this->getLocalMax().y));
	vertices.push_back(Vector2f(this->getLocalMax().x, this->getLocalMin().y));
	vertices.push_back(Vector2f(this->getLocalMax()));

	//Rotate the vertices if the box is rotated
	for (auto& vertex : vertices) {
		rotateVector2f(vertex, this->getRigidbody()->getRotation(), this->getRigidbody()->getPosition());
	}

	return vertices;
}

Rigidbody2D* Box::getRigidbody() {
	return rigidbody;
}

void Box::setRigidbody(Rigidbody2D* rigidbody) {
	this->rigidbody = rigidbody;
}

Type Box::getType() {
	return Type::Box;
}

void Box::setSize(Vector2f size) {
	this->size = size;
	this->halfSize = size / 2.f;
	RectangleShape::setOrigin(halfSize);
	RectangleShape::setSize(size);
}

//Updates the properties of this class from the rigidbody
void Box::updateFromRigidbody() {
	//Update RectangleShape
	RectangleShape::setRotation(rigidbody->getRotation());
	RectangleShape::setPosition(rigidbody->getPosition());
}