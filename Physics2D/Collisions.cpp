#include "Collisions.h"

using namespace Physics2D;
using sf::Vector2f;

namespace Physics2D {
	//=====================================
	// Find collision features between any combination of two colliders using overloaded methods:
	// Supports Circle VS Circle
	//			Circle VS AABB
	//			Circle VS Box
	//			AABB VS AABB
	//			AABB VS Box
	//			Box VS Box
	//=====================================

	CollisionManifold findCollisionFeatures(Collider2D* c1, Collider2D* c2) {
		//Test different combinations of collider objects:

		//Circle vs Circle
		if (c1->getType() == Type::Circle && c2->getType() == Type::Circle) {
			Circle* circ1 = static_cast<Circle*>(c1);
			Circle* circ2 = static_cast<Circle*>(c2);
			return findCollisionFeatures(circ1, circ2);
		}

		// Circle vs AABB
		if (c1->getType() == Type::Circle && c2->getType() == Type::AABB) {
			Circle* circ = static_cast<Circle*>(c1);
			AABB* ab = static_cast<AABB*>(c2);
			return findCollisionFeatures(circ, ab);
		}

		if (c1->getType() == Type::AABB && c2->getType() == Type::Circle) {
			AABB* ab = static_cast<AABB*>(c1);
			Circle* circ = static_cast<Circle*>(c2);
			return findCollisionFeatures(circ, ab);
		}

		// Circle vs Box
		if (c1->getType() == Type::Circle && c2->getType() == Type::Box) {
			Circle* c = static_cast<Circle*>(c1);
			Box* b = static_cast<Box*>(c2);
			return findCollisionFeatures(c, b);
		}

		if (c1->getType() == Type::Box && c2->getType() == Type::Circle) {
			Box* b = static_cast<Box*>(c1);
			Circle* c = static_cast<Circle*>(c2);
			return findCollisionFeatures(c, b);
		}
		
		// AABB vs AABB
		if (c1->getType() == Type::AABB && c2->getType() == Type::AABB) {
			AABB* ab1 = static_cast<AABB*>(c1);
			AABB* ab2 = static_cast<AABB*>(c2);
			return findCollisionFeatures(ab1, ab2);
		}

		// AABB vs Box
		if (c1->getType() == Type::AABB && c2->getType() == Type::Box) {
			AABB* ab = static_cast<AABB*>(c1);
			Box* b = static_cast<Box*>(c2);
			return findCollisionFeatures(ab, b);
		}

		if (c1->getType() == Type::Box && c2->getType() == Type::AABB) {
			Box* b = static_cast<Box*>(c1);
			AABB* ab = static_cast<AABB*>(c2);
			return findCollisionFeatures(ab, b);
		}

		// Box vs Box
		if (c1->getType() == Type::Box && c2->getType() == Type::Box) {
			Box* b1 = static_cast<Box*>(c1);
			Box* b2 = static_cast<Box*>(c2);
			return findCollisionFeatures(b1, b2);
		}

		return CollisionManifold();
	}

	//=====================================
	// Circle VS Circle
	//=====================================
	CollisionManifold findCollisionFeatures(Circle* c1, Circle* c2) {
		CollisionManifold result = CollisionManifold();
		float sumRadii = c1->getRadius() + c2->getRadius();
		Vector2f distance = c2->getCenter() - c1->getCenter();

		//Check if circles are colliding and return if not
		if (floatGT(vLengthSquared(distance), powf(sumRadii, 2.f))) return result;

		//Calculate depth and divide by two
		float depth = fabsf(vLength(distance) - sumRadii) / 2.f;
		Vector2f normal(distance);
		vNormalize(normal);

		Vector2f collisionPoint = c1->getCenter() + normal * (c1->getRadius() - depth);
		
		result = CollisionManifold(normal, depth);
		result.addContactPoint(collisionPoint);
		return result;
	}

	//=====================================
	// Circle VS AABB
	//=====================================
	CollisionManifold findCollisionFeatures(Circle* c, AABB* ab) {
		CollisionManifold result = CollisionManifold();
		Vector2f center = c->getCenter();

		//Step 1: Find if objects are colliding:
		if (!circleVSAABB(*c, *ab)) return result;

		//Step 2: Find the normal vector:

		// Catch the case where circle center is inside AABB:
		if (pointInAABB(center, *ab)) {
		}

		// Get closest point to circle center:
		int closestX, closestY;

		if (abs(center.x - ab->getMax().x) <= abs(center.x - ab->getMin().x)) {
			closestX = ab->getMax().x;
		}
		else {
			closestX = ab->getMin().x;
		}
		if (abs(center.y - ab->getMax().y) <= abs(center.y - ab->getMin().y)) {
			closestY = ab->getMax().y;
		}
		else {
			closestY = ab->getMin().y;
		}

		// Step 3: Compute normal vector

		if (center.x >= ab->getMin().x && center.x <= ab->getMax().x) {
			closestX = center.x;
		}
		else if (center.y >= ab->getMin().x && center.y <= ab->getMax().y) {
			closestY = center.y;
		}

		Vector2f normal = -1.f * (center - Vector2f(closestX, closestY));
		float normalLength = vLength(normal);
		normal = normal / normalLength;

		// Step 5: Generate and return collision manifold:
		float depth = c->getRadius() - normalLength;
		result = CollisionManifold(normal, depth);
		result.addContactPoint(c->getCenter() + normal * (c->getRadius() - depth));
		return result;

	}

	CollisionManifold findCollisionFeatures(AABB* ab, Circle* c) {
		// Return overloaded method
		return findCollisionFeatures(c, ab);
	}


	//=====================================
	// Circle VS Box
	//=====================================
	CollisionManifold findCollisionFeatures(Circle* c, Box* b) {
		// TODO: Implement
		CollisionManifold result = CollisionManifold();

		// Check if intersecting, and return result if not
		if (!circleVSBox(*c, *b)) return result;

		// Transform circle, c into box's local coordinates (rotate opposite direction of box)
		Vector2f r = c->getCenter() - b->getCenter();
		rotateVector2f(r, -1.f * b->getRotation(), Vector2f(0.f, 0.f));
		Circle c_local = Circle(c->getRadius(), b->getCenter() + r);

		// Get box's AABB:
		AABB ab = AABB(b->getLocalMin(), b->getLocalMax());

		// Find the collision manifold between the AABB of the box, and the local circle
		result = findCollisionFeatures(&ab, &c_local);

		// Transform the local collision manifold to the real one
		result.rotate(b->getRotation(), b->getCenter());

		return result;
	}

	CollisionManifold findCollisionFeatures(Box* b, Circle* c) {
		// Return overloaded method
		return findCollisionFeatures(c, b);
	}

	//=====================================
	// AABB VS AABB
	//=====================================
	CollisionManifold findCollisionFeatures(AABB* ab1, AABB* ab2) {

		CollisionManifold result = CollisionManifold();

		// Check if intersecting, and return empty manifold if not:
		if (!aabbVSAABB(*ab1, *ab2)) return result;
		result.setColliding(true);

		// Find faces that are overlapping:
		Vector2f relativePosition = ab2->getCenter() - ab1->getCenter();
		Vector2f relativeVelocity = ab2->getRigidbody()->getLinearVelocity() - ab1->getRigidbody()->getLinearVelocity();
		float overlapX = 0.0f;
		float overlapY = 0.0f;

		if (floatCompare(relativeVelocity.x, 0.f)) {
			if (floatGT(relativePosition.y, 0.f)) {
				result.setNormal(Vector2f(0.f,1.f));
				result.setDepth(ab1->getMax().y - ab2->getMin().y);
			}
			else {
				result.setNormal(Vector2f(0.f, -1.f));
				result.setDepth(ab2->getMax().y - ab1->getMin().y);

			}
			result.addContactPoint(Vector2f());
			return result;
		}
		else if (floatCompare(relativeVelocity.y, 0.f)) {
			if (floatGT(relativePosition.x, 0.f)) {
				result.setNormal(Vector2f(1.f, 0.f));
				result.setDepth(ab1->getMax().x - ab2->getMin().x);
			}
			else {
				result.setNormal(Vector2f(-1.f, 0.f));
				result.setDepth(ab2->getMax().x - ab1->getMin().x);

			}
			result.addContactPoint(Vector2f());
			return result;
		}

		if (floatGT(relativePosition.x, 0.0f)) {
			overlapX = ab1->getMax().x - ab2->getMin().x;
		}
		else {
			overlapX = ab1->getMin().x - ab2->getMax().x;
		}

		if (floatGT(relativePosition.y, 0.0f)) {
			overlapY = ab1->getMax().y - ab2->getMin().y;
		}
		else {
			overlapY = ab1->getMin().y - ab2->getMax().y;
		}

		// Figure out which overlap turned positive first
		if (floatGT(abs(overlapX / relativeVelocity.x), abs(overlapY / relativeVelocity.y))) {
			// Time_X > Time_Y, so they collided on the vertical sides
			result.setNormal(Vector2f(0.f, (overlapY > 0) - (overlapY < 0)));
			result.setDepth(overlapY);
		}
		else {
			// Time_Y > Time_X, so they collided on the horizontal sides
			result.setNormal(Vector2f((overlapX > 0) - (overlapX < 0), 0.f));
			result.setDepth(overlapX);
		}

		result.addContactPoint(Vector2f());

		return result;
	}

	//=====================================
	// AABB VS Box
	//=====================================
	CollisionManifold findCollisionFeatures(AABB* ab, Box* b) {
		CollisionManifold result = CollisionManifold();

		// Check if the two objects are colliding and return result if not
		if (!aabbVSBox(*ab, *b)) return result;
		result.setColliding(true);

		AABB* ab2 = b->getAABB();

		result = findCollisionFeatures(ab2, ab);
		return result;
	}

	CollisionManifold findCollisionFeatures(Box* b, AABB* ab) {
		// Return overloaded method
		return findCollisionFeatures(ab, b);
	}

	//=====================================
	// Box VS Box
	//=====================================
	CollisionManifold findCollisionFeatures(Box* b1, Box* b2) {
		// TODO: Implement
		return CollisionManifold();
	}

}