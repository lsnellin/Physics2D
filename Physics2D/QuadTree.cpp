#include "QuadTree.h"

using namespace Physics2D;
using namespace sf;

QuadTree::QuadTree(AABB map, int threshold, int maxDepth) :
	map(map),
	threshold(threshold),
	maxDepth(maxDepth)
{}

bool QuadTree::add(PhysicsObject& data) {
	return true;
}