#pragma once

#include "CollisionManifold.h"
#include "Circle.h"
#include "AABB.h"
#include "Box.h"
#include <cmath>

namespace Physics2D {
	Physics2D::CollisionManifold findCollisionPoints(Physics2D::Circle c1, Physics2D::Circle c2);
}