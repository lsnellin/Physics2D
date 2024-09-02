#pragma once

#include "AABB.h"

#include <SFML/Graphics.hpp>

namespace Physics2D {
	struct QuadData {
		PhysicsObject* data;
	};

	class QuadTree {
	private:
		AABB map;

		std::vector<QuadTree> children;

		int depth;
		int maxDepth;
		int threshold;
	public:
		QuadTree(AABB map, int threshold, int maxDepth);
	};
}

