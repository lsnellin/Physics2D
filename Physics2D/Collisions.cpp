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

		if (c1->getType() == Type::Circle && c2->getType() == Type::AABB) {
			return findCollisionFeatures(c1, c2);
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

	CollisionManifold findCollisionFeatures(AABB* ab, Circle* c) {
		return findCollisionFeatures(c, ab);
	}

	CollisionManifold findCollisionFeatures(Circle* c, AABB* ab) {
		return findCollisionFeatures(c, ab);
	}
}