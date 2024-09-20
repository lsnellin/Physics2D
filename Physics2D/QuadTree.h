#pragma once

#include "AABB.h"

#include <SFML/Graphics.hpp>

namespace Physics2D {
	class QuadTree {
	private:
		AABB map;

		std::vector<QuadTree> children;

		int maxDepth;
		int threshold;
	public:
		QuadTree(AABB map, int threshold, int maxDepth);

		bool add(PhysicsObject &data);
	};
}

