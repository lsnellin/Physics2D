#include "Circle.h"

using namespace Physics2D;
using sf::Vector2f;

Circle::Circle() :
	Circle(1.0f, sf::Vector2f(0,0))
{
}

Circle::Circle(float radius, Vector2f center) :
	rigidbody(new Rigidbody2D(center, 0.f, this)),
	radius(radius)
{
	setCenter(center);
	setRadius(radius);
	CircleShape::setOrigin(Vector2f(radius, radius));
}

Circle::~Circle() {
	delete rigidbody;
}

Rigidbody2D* Circle::getRigidbody() {
	return rigidbody;
}

float Circle::getRadius() {
	return this->radius;
}

Vector2f Circle::getCenter() {
	return this->rigidbody->getPosition();
}

Type Circle::getType() {
	return Type::Circle;
}

void Circle::setCenter(Vector2f center) {
	this->rigidbody->setPosition(center);
	CircleShape::setPosition(center);
}

void Circle::setRadius(float radius) {
	this->radius = radius;
	CircleShape::setRadius(radius);
}

void Circle::setRigidbody(Rigidbody2D* rigidbody) {
	this->rigidbody = rigidbody;
}

void Circle::updateFromRigidbody() {
	CircleShape::setPosition(rigidbody->getPosition());
}