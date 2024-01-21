#include "CollisionManifold.h"

using namespace Physics2D;
using sf::Vector2f;
using std::vector;

CollisionManifold::CollisionManifold() :
	normal(),
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

bool CollisionManifold::getIsColliding() {
	return this->isColliding;
}