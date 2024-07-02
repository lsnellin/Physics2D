#include "CollisionManifold.h"

using namespace Physics2D;
using sf::Vector2f;
using std::vector;

CollisionManifold::CollisionManifold() :
	normal(Vector2f()),
	contactPoints(),
	depth(),
	isColliding(false)
{}

CollisionManifold::CollisionManifold(Vector2f normal, float depth) :
	normal(normal),
	contactPoints(),
	depth(depth),
	isColliding(true)
{}

void CollisionManifold::addContactPoint(Vector2f point) {
	contactPoints.push_back(point);
}

float CollisionManifold::getDepth() {
	return this->depth;
}

Vector2f CollisionManifold::getNormal() {
	return this->normal;
}

vector<Vector2f> CollisionManifold::getContactPoints() {
	return this->contactPoints;
}

bool CollisionManifold::getColliding() {
	return this->isColliding;
}

void CollisionManifold::rotate(float r, Vector2f origin) {
	// Rotate normal around (0, 0):
	rotateVector2f(this->normal, r, Vector2f(0.f, 0.f));

	// Rotate contact points around origin:
	for (Vector2f contactPoint : this->contactPoints) {
		rotateVector2f(contactPoint, r, origin);
	}
}

void CollisionManifold::setNormal(Vector2f normal) {
	this->normal = normal;
}

void CollisionManifold::setDepth(float depth) {
	this->depth = depth;
}