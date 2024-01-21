#include "PhysicsSystem2D.h"

using namespace Physics2D;
using sf::Vector2f;
using std::vector;

PhysicsSystem2D::PhysicsSystem2D(float fixedUpdateDT, Vector2f gravity) :
	forceRegistry(ForceRegistry()),
	rigidbodies({}),
	bodies1({}),
	bodies2({}),
	collisions({}),

	fixedUpdateDT(fixedUpdateDT), 
	gravity(Gravity2D(gravity))
{}

void PhysicsSystem2D::update(float dt) {
	fixedUpdate();
}

void PhysicsSystem2D::fixedUpdate() {
	//Update Forces
	forceRegistry.updateForces(fixedUpdateDT);

	//Find collisions (OPTIMIZE)
	bodies1.clear();
	bodies2.clear();
	collisions.clear();

	//Check each possible combination of objects for a collision
	for (vector<Rigidbody2D*>::iterator body1 = rigidbodies.begin(); body1 < rigidbodies.end(); body1++) {
		for (vector<Rigidbody2D*>::iterator body2 = body1 + 1; body2 < rigidbodies.end(); body2++) {
			Collider2D c1 = (*body1)->getCollider();
			Collider2D c2 = (*body2)->getCollider();
		}
	}

	//Resolve collisions

	//TODO: Update Rigidbody velocities:
	for (vector<Rigidbody2D*>::iterator rb = rigidbodies.begin(); rb < rigidbodies.end(); rb++) {
		(*rb)->physicsUpdate(fixedUpdateDT);
	}
}

void PhysicsSystem2D::addRigidbody(Rigidbody2D *rb) {
	rigidbodies.push_back(rb);
	forceRegistry.add(&gravity, rb);
}