#include "Gravity2D.h"

using namespace Physics2D;
using sf::Vector2f;


Gravity2D::Gravity2D(Vector2f force) {
	this->gravity = force;
}

void Gravity2D::updateForce(Rigidbody2D* rb, float dt) {
	rb->addForce(gravity * rb->getMass());
}