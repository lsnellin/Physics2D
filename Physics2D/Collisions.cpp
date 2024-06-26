#include "Collisions.h"

using namespace Physics2D;
using sf::Vector2f;

namespace Physics2D {
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
	}

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

		// Step 4: Get contact point

		// Step 5: Generate and return collision manifold:
		float depth = c->getRadius() - normalLength;
		result = CollisionManifold(normal, depth);
		result.addContactPoint(c->getCenter() + normal * (c->getRadius() - depth));
		return result;

	}

	CollisionManifold findCollisionFeatures(AABB* ab, Circle* c) {
		return findCollisionFeatures(c, ab);
	}

}