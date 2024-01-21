#include "Collisions.h"

using namespace Physics2D;
using sf::Vector2f;

namespace Physics2D {
	CollisionManifold findCollisionPoints(Circle c1, Circle c2) {
		CollisionManifold result = CollisionManifold();
		float sumRadii = c1.getRadius() + c2.getRadius();
		Vector2f distance = c2.getCenter() - c1.getCenter();

		//Check if circles are colliding and return if not
		if (floatGT(vLengthSquared(distance), powf(sumRadii, 2.f))) return result;

		//Calculate depth and divide by two
		float depth = fabsf(vLength(distance) - sumRadii) / 2.f;
		Vector2f normal(distance);
		vNormalize(&normal);

		Vector2f collisionPoint = c1.getCenter() + normal * (c1.getRadius() - depth);
		
		result = CollisionManifold(normal, depth);
		result.addContactPoint(collisionPoint);
		return result;
	}
}