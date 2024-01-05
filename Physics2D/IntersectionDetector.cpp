#include "IntersectionDetector.h"

namespace Physics2D {
	using Physics2D::floatLT;
	using Physics2D::floatGT;
	using sf::Vector2f;
	using std::pow;

	bool pointInBox(Vector2f point, Physics2D::Box box) {
		//Copy point and rotate to box's local space:
		Vector2f localPoint = Vector2f(point);
		Physics2D::rotateVector2f(&localPoint, box.getRigidbody().getRotation(), box.getRigidbody().getPosition());

		//Check if point lies within the bounds of aabb
		sf::Vector2f max = box.getMax();
		sf::Vector2f min = box.getMin();

		return !floatLT(localPoint.x, min.x)
			&& !floatGT(localPoint.x, max.x)
			&& !floatLT(localPoint.y, min.y)
			&& !floatGT(localPoint.y, max.y);
	}

	bool pointInAABB(sf::Vector2f point, Physics2D::AABB aabb) {
		//Check if point lies within the bounds of aabb
		sf::Vector2f max = aabb.getMax();
		sf::Vector2f min = aabb.getMin();

		return !floatLT(point.x, min.x)
			&& !floatGT(point.x, max.x)
			&& !floatLT(point.y, min.y)
			&& !floatGT(point.y, max.y);
	}

	bool pointInCirlce(sf::Vector2f point, Physics2D::Circle circle) {
		//Check if point lies within the circle
		sf::Vector2f dif = circle.getCenter() - point;
		float dist = pow(dif.x, 2) + pow(dif.y, 2);

		return !floatGT(dist, pow(circle.getRadius(), 2));
	}
};