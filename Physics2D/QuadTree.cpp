#include "QuadTree.h"

using namespace Physics2D;
using namespace sf;

QuadTree::QuadTree(AABB map, int threshold) 
	boundary(map),
	threshold(threshold)
{}


Node::Node()