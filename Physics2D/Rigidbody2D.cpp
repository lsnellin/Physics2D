#include "Rigidbody2D.h"

using namespace Physics2D;
using namespace sf;

Rigidbody2D::Rigidbody2D() :
position(Vector2f()), 
rotation(0.0f)
{
}

Vector2f Rigidbody2D::getPosition() {
	return this->position;
}

float Rigidbody2D::getRotation() {
	return this->rotation;
}

void Rigidbody2D::setPosition(Vector2f position) {
	this->position = position;
}

void Rigidbody2D::setRotation(float rotation) {
	this->rotation = rotation;
}