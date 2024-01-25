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
	impulseIterations(8),
	gravity(new Gravity2D(gravity))
{}

PhysicsSystem2D::~PhysicsSystem2D() {
	delete gravity;
}

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

	CollisionManifold result;

	//Check each possible combination of objects for a collision
	for (vector<Rigidbody2D*>::iterator body1 = rigidbodies.begin(); body1 < rigidbodies.end(); body1++) {
		for (vector<Rigidbody2D*>::iterator body2 = body1 + 1; body2 < rigidbodies.end(); body2++) {
			Collider2D* c1 = (*body1)->getCollider();
			Collider2D* c2 = (*body2)->getCollider();

			if (c1 != nullptr && c2 != nullptr && !((*body1)->hasInfiniteMass() && (*body2)->hasInfiniteMass())) {
				result = findCollisionFeatures(c1, c2);
			}

			if (result.getColliding()) {
				bodies1.push_back(*body1);
				bodies2.push_back(*body2);
				collisions.push_back(result);

			}
		}
	}
	
	//Resolve collisions
	for (int i = 0; i < impulseIterations; i++) {
		for (int j = 0; j < collisions.size(); j++) {
			int numPoints = collisions[j].getContactPoints().size();
			for (int k = 0; k < numPoints; k++) {
				Rigidbody2D* rb1 = bodies1[j];
				Rigidbody2D* rb2 = bodies2[j];
				applyImpulse(*rb1, *rb2, collisions[j]);
			}
		}
	}

	//TODO: Update Rigidbody velocities:
	for (vector<Rigidbody2D*>::iterator rb = rigidbodies.begin(); rb < rigidbodies.end(); rb++) {
		(*rb)->physicsUpdate(fixedUpdateDT);
	}
}

void PhysicsSystem2D::applyImpulse(Rigidbody2D& a, Rigidbody2D& b, CollisionManifold m) {
	float iMass1 = a.getInverseMass();
	float iMass2 = b.getInverseMass();
	float iMassSum = iMass1 + iMass2;
	if (!floatGT(iMassSum, 0.f)) return;

	Vector2f relativeVelocity = b.getLinearVelocity() - a.getLinearVelocity();
	Vector2f relativeNormal = m.getNormal();
	vNormalize(relativeNormal);

	//Check if objects are already moving away from each other
	if (floatGT(vDot(relativeVelocity, relativeNormal), 0.0f)) return;

	//Calculate impulse and apply it:
	float e = fminf(a.getCor(), b.getCor());
	float numerator = vDot(relativeVelocity, relativeNormal) * -(1.f + e);
	float j = numerator / iMassSum;

	if (m.getContactPoints().size() > 0 && floatGT(j, 0.f)) {
		j /= (float)m.getContactPoints().size();
	}

	Vector2f impulse = j * relativeNormal;
	a.setLinearVelocity(a.getLinearVelocity() + impulse * iMass1 * -1.f);
	b.setLinearVelocity(b.getLinearVelocity() + impulse * iMass2);
}

void PhysicsSystem2D::addRigidbody(Rigidbody2D* rb) {
	rigidbodies.push_back(rb);
	forceRegistry.add(gravity, rb);
}