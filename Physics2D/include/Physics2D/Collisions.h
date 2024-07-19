#pragma once

#include "CollisionManifold.h"
#include "Circle.h"
#include "AABB.h"
#include "Box.h"
#include "pUtil.h"
#include "IntersectionDetector.h"
#include <cmath>

namespace Physics2D {
	Physics2D::CollisionManifold findCollisionFeatures(Physics2D::Collider2D* c1, Physics2D::Collider2D* c2);

	Physics2D::CollisionManifold findCollisionFeatures(Physics2D::Circle* c1, Physics2D::Circle* c2);
	Physics2D::CollisionManifold findCollisionFeatures(Physics2D::Circle* c, Physics2D::AABB* ab);
	Physics2D::CollisionManifold findCollisionFeatures(Physics2D::AABB* ab, Physics2D::Circle* c);
	Physics2D::CollisionManifold findCollisionFeatures(Physics2D::Circle* c, Physics2D::Box* b);
	Physics2D::CollisionManifold findCollisionFeatures(Physics2D::Box* b, Physics2D::Circle* c);

	Physics2D::CollisionManifold findCollisionFeatures(Physics2D::AABB* ab1, Physics2D::AABB* ab2);
	Physics2D::CollisionManifold findCollisionFeatures(Physics2D::AABB* ab, Physics2D::Box* b);
	Physics2D::CollisionManifold findCollisionFeatures(Physics2D::Box* b, Physics2D::AABB* ab);

	Physics2D::CollisionManifold findCollisionFeatures(Physics2D::Box* b1, Physics2D::Box* b2);


}