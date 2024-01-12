#include "IntersectionDetector.h"

namespace Physics2D {
	using namespace Physics2D;
	using sf::Vector2f;
	using std::pow;
	using std::fmaxf;
	using std::fminf;

	// =========================
	// Point vs Primitive Tests:
	// =========================

	//Test if a point lies on a line
	bool pointOnLine(Vector2f point, Line line) {
		//Solve for equation of line:
		Vector2f p1 = line.getStart();
		Vector2f p2 = line.getEnd();

		float dx = p2.x - p1.x;
		float dy = p2.y - p1.y;
		float m = dy / dx;
		float b = p1.y - m * p1.x;

		return floatCompare(point.y, m * point.x + b);
	}

	//Test if a point is within a box
	bool pointInBox(Vector2f point, Box box) {
		//Copy point and rotate to box's local space:
		Vector2f localPoint = Vector2f(point);
		rotateVector2f(&localPoint, box.getRigidbody().getRotation(), box.getRigidbody().getPosition());

		//Check if point lies within the bounds of aabb
		sf::Vector2f max = box.getMax();
		sf::Vector2f min = box.getMin();

		return !floatLT(localPoint.x, min.x)
			&& !floatGT(localPoint.x, max.x)
			&& !floatLT(localPoint.y, min.y)
			&& !floatGT(localPoint.y, max.y);
	}

	//Test if a point is within an AABB
	bool pointInAABB(Vector2f point, AABB aabb) {
		//Check if point lies within the bounds of aabb
		Vector2f min = aabb.getMin();
		Vector2f max = aabb.getMax();

		return !floatLT(point.x, min.x)
			&& !floatGT(point.x, max.x)
			&& !floatLT(point.y, min.y)
			&& !floatGT(point.y, max.y);
	}

	//Tests if a point is within a circle
	bool pointInCircle(Vector2f point, Circle circle) {
		//Check if point lies within the circle
		sf::Vector2f dif = circle.getCenter() - point;
		float dist = pow(dif.x, 2) + pow(dif.y, 2);

		return !floatGT(dist, pow(circle.getRadius(), 2));
	}

	// ========================
	// Line vs Primitive Tests:
	// ========================

	//Tests if a line intersects a circle
	bool lineVSCircle(Line line, Circle circle) {
		if (pointInCircle(line.getStart(), circle) || pointInCircle(line.getEnd(), circle)) {
			return true;
		}

		Vector2f ab = line.getVector(); //The line segment
		Vector2f circleCenter = circle.getCenter();
		Vector2f ac = circleCenter - line.getStart(); //Line from line start to circle center

		float ratio = vDot(ab, ac) / vDot(ab, ab);

		/*If the ratio between the radius projection onto the line and the line itself is not between
		zero and one, then the closest point along the line is not on the line.*/
		if (floatLT(ratio, 0.0f) || floatGT(ratio, 1.0f)) {
			return false;
		}

		//line.getStart() + ab * ratio is the closest point to the circle along the line
		return pointInCircle(line.getStart() + ab * ratio, circle);
	}

	//Tests if a line intersects an AABB
	bool lineVSAABB(Line line, AABB aabb) {
		//If either end point is in the box, return true immediately:
		if (pointInAABB(line.getStart(), aabb) || pointInAABB(line.getEnd(), aabb)) return true;

		//Set up unit vector and get the inverse of the dimensions
		Vector2f lineUnitVector = line.getVector();
		vNormalize(&lineUnitVector);
		lineUnitVector.x = floatCompare(lineUnitVector.x, 0.f) ? 0.f : 1.f / lineUnitVector.x; //Invert x w/o dividing by 0
		lineUnitVector.y = floatCompare(lineUnitVector.y, 0.f) ? 0.f : 1.f / lineUnitVector.y; //Invert y w/o dividing by 0

		Vector2f min = aabb.getMin() - line.getStart();
		Vector2f max = aabb.getMax() - line.getStart();

		min.x *= lineUnitVector.x;
		min.y *= lineUnitVector.y;
		max.x *= lineUnitVector.x;
		max.y *= lineUnitVector.y;

		float tmin = fmaxf(fminf(min.x, max.x), fminf(min.y, max.y));
		float tmax = fminf(fmaxf(min.x, max.x), fmaxf(min.y, max.y));

		if (floatLT(tmax, 0.f) || floatGT(tmin, tmax)) return false;
		float t = floatLT(tmin, 0.f) ? tmax : tmin;

		return floatGT(t, 0.f) && floatLT(pow(t, 2.f), pow(line.getVector().x, 2.f) + pow(line.getVector().y, 2.f));
	}

	//Tests if a line intersects a rotated box
	bool lineVSBox(Line line, Box box) {
		float angle = box.getRigidbody().getRotation();
		Vector2f center = box.getRigidbody().getPosition();
		Vector2f localStart(line.getStart());
		Vector2f localEnd(line.getEnd());

		//Rotate starting and ending points
		rotateVector2f(&localStart, angle, center);
		rotateVector2f(&localEnd, angle, center);

		Line localLine = Line(localStart, localEnd);
		AABB aabb = AABB(box.getMin(), box.getMax());

		return lineVSAABB(localLine, aabb);
	}

	//Raycasts a ray against a circle and stores the result in the given location
	bool raycast(Circle circle, Ray ray, RaycastResult* result) {
		RaycastResult::reset(result);
		Vector2f originToCircle = circle.getCenter() - ray.getOrigin();
		float originToCircleSquared = vLengthSquared(originToCircle);
		float rSquared = powf(circle.getRadius(), 2.f);

		//Get dot product of origin to circle and ray direction:
		float a = vDot(originToCircle, ray.getDirection());
		float bSquared = originToCircleSquared - powf(a, 2.f);
	
		//If the r^2 < b^2, then the raycast did not hit
		//b > r, and since edge B is perpendicular to the raycast, so the ray missed the circle
		if (floatLT(rSquared, bSquared)) return false;

		//Now we take the square root because we know r^2 - b^2 > 0, we can take the sqrt
		float f = sqrtf(rSquared - bSquared);
		float t = 0;

		//If length from the origin of the ray to the center of the circle < r
		//Then the ray must start inside of the circle. So t = f + a
		if (floatLT(originToCircleSquared, rSquared)) t = f + a;
		else t = a - f;

		//The point on the circle is equal to origin + t * ray direction
		Vector2f point = ray.getOrigin() + (ray.getDirection() * t);

		//Vector from center of the circle to the point is the direction that the ray will "Bounce"
		Vector2f normal = point - circle.getCenter();
		//Normalize without using the square root function:
		normal.x /= circle.getRadius();
		normal.y /= circle.getRadius();
		//vNormalize(&normal); //Normalize

		//Set the raycast result and return true
		result->init(point, normal, t, true);
		return true;
	}

	//Raycasts a ray against an AABB and stores the result in the given location
	bool raycast(AABB aabb, Ray ray, RaycastResult *result) {
		RaycastResult::reset(result);
		//Set up unit vector and get the inverse of the dimensions
		Vector2f lineUnitVector = ray.getDirection();

		lineUnitVector.x = floatCompare(lineUnitVector.x, 0.f) ? 
			std::numeric_limits<float>::infinity() : 1.f / lineUnitVector.x; //Invert x w/o dividing by 0
		lineUnitVector.y = floatCompare(lineUnitVector.y, 0.f) ? 
			std::numeric_limits<float>::infinity() : 1.f / lineUnitVector.y; //Invert y w/o dividing by 0

		Vector2f min = aabb.getMin() - ray.getOrigin();
		Vector2f max = aabb.getMax() - ray.getOrigin();

		float nearX = min.x * lineUnitVector.x;
		float nearY = min.y * lineUnitVector.y;
		float farX = max.x * lineUnitVector.x;
		float farY = max.y * lineUnitVector.y;

		float tmin = fmaxf(fminf(nearX, farX), fminf(nearY, farY));
		float tmax = fminf(fmaxf(nearX, farX), fmaxf(nearY, farY));

		if (floatLT(tmax, 0.f) || floatGT(tmin, tmax)) return false;
		float t = floatLT(tmin, 0.f) ? tmax : tmin;

		//If t is not negative and the length of t is less than the maximum length of the ray, it hit
		bool hit = !floatLT(t, 0.f); // && floatLT(powf(t, 2.f), powf(ray.getMaximum(), 2.f));
		if (!hit) return false;

		Vector2f point = ray.getOrigin() + ray.getDirection() * t;
		Vector2f normal = ray.getDirection() * -1.f;

		result->init(point, normal, t, hit);

		return true;
	}

	//Raycasts a ray against a Box with rotation and stores the result in the given location
	bool raycast(Box box, Ray ray, RaycastResult* result) {
		//Reset result:
		RaycastResult::reset(result);

		//Transform ray into box's local space
		float angle = box.getRigidbody().getRotation();
		Vector2f center = box.getRigidbody().getPosition();
		ray.rotate(angle, center);

		//Perform raycast using local ray
		AABB aabb = AABB(box.getMin(), box.getMax());
		if (!raycast(aabb, ray, result)) return false;

		//If raycast hit, unrotate the result and return true:
		Vector2f point = result->getPoint();
		Vector2f normal = result->getNormal();
		rotateVector2f(&point, -angle, center);
		rotateVector2f(&normal, -angle, center);
		result->init(point, normal, result->getT(), true);
		return true;
	}

	// ==========================
	// Circle Vs. Primitive Tests
	// ==========================

	//Checks if a circle and a line are intersecting
	bool circleVSLine(Circle circle, Line line) {
		return lineVSCircle(line, circle);
	}

	//Checks if two circles are intersecting
	bool circleVSCircle(Circle circle1, Circle circle2) {
		Vector2f centerDistance = circle2.getCenter() - circle1.getCenter();
		float combinedRadius = circle1.getRadius() + circle2.getRadius();

		return !floatGT(vLengthSquared(centerDistance), powf(combinedRadius, 2.f));
	}

	//Checks if a circle and an aabb are intersecting
	bool circleVSAABB(Circle circle, AABB aabb) {
		Vector2f min = aabb.getMin();
		Vector2f max = aabb.getMax();
		Vector2f closestPoint(circle.getCenter());

		if (floatLT(closestPoint.x, min.x)) {
			closestPoint.x = min.x;
		}
		else if (floatGT(closestPoint.x, max.x)) {
			closestPoint.x = max.x;
		}

		if (floatLT(closestPoint.y, min.y)) {
			closestPoint.y = min.y;
		}
		else if (floatGT(closestPoint.y, max.y)) {
			closestPoint.y = max.y;
		}

		Vector2f centerToPoint(closestPoint - circle.getCenter());

		return (!floatGT(vLengthSquared(centerToPoint), powf(circle.getRadius(), 2)));
	}

	//Checks if a circle and a box with rotation are intersecting
	bool circleVSBox(Circle circle, Box box) {
		//Treat box as if it weren't rotated:
		Vector2f min(0.f, 0.f);
		Vector2f max(box.getHalfsize() * 2.f);

		//Create circle in box local space:
		Vector2f r = circle.getCenter() - box.getRigidbody().getPosition();
		rotateVector2f(&r, -box.getRigidbody().getRotation(), Vector2f(0.f,0.f));
		r += box.getHalfsize();

		Circle localCircle = Circle(circle.getRadius(), r);
		AABB aabb = AABB(min, max);
		return circleVSAABB(localCircle, aabb);
	}

	// ==========================
	// AABB Vs. Primitive Tests
	// ==========================

	//Checks if an aabb and a line are intersecting
	bool aabbVSLine(AABB aabb, Line line) {
		return lineVSAABB(line, aabb);
	}

	//Checks if an aabb and a circle are intersecting
	bool aabbVSCircle(AABB aabb, Circle circle) {
		return circleVSAABB(circle, aabb);
	}

	//Checks if two AABB's are intersecting
	bool aabbVSAABB(AABB aabb1, AABB aabb2) {
		//AABBs have axis (1,0) and (0,1)
		//Return true if aabb overlaps on both axis
		return overlapOnAxis(aabb1, aabb2, Vector2f(1.f, 0.f))
			&& overlapOnAxis(aabb1, aabb2, Vector2f(0.f, 1.f));
	}

	bool aabbVSBox(AABB aabb, Box box) {
		std::vector<Vector2f> axes;

		axes.push_back(Vector2f(1.f, 0.f)); //AABB x axis
		axes.push_back(Vector2f(0.f, 1.f)); //AABB y axis
		axes.push_back(Vector2f(1.f, 0.f)); //Box x axis
		axes.push_back(Vector2f(0.f, 1.f)); //Box y axis

		rotateVector2f(&axes[2], box.getRigidbody().getRotation(), box.getRigidbody().getPosition());
		rotateVector2f(&axes[3], box.getRigidbody().getRotation(), box.getRigidbody().getPosition());

		for (auto& axis : axes) {
			if (!overlapOnAxis(aabb, box, axis)) return false;
		}

		return true;
	}

	// =======================
	// Box Vs. Primitive Tests
	// =======================

	//Checks if a box and a line intersect
	bool boxVSLine(Box box, Line line) {
		return lineVSBox(line, box);
	}

	//Checks if a box and a circle intersect
	bool boxVSCircle(Box box, Circle circle) {
		return circleVSBox(circle, box);
	}

	//Checks if a box and an AABB intersect
	bool boxVSAABB(Box box, AABB aabb) {
		return aabbVSBox(aabb, box);
	}

	//Checks if two boxes intersect
	bool boxVSBox(Box box1, Box box2) {
		std::vector<Vector2f> axes;

		axes.push_back(Vector2f(1.f, 0.f)); //Box1 x axis
		axes.push_back(Vector2f(0.f, 1.f)); //Box1 y axis
		axes.push_back(Vector2f(1.f, 0.f)); //Box2 x axis
		axes.push_back(Vector2f(0.f, 1.f)); //Box2 y axis

		rotateVector2f(&axes[0], box1.getRigidbody().getRotation(), box1.getRigidbody().getPosition());
		rotateVector2f(&axes[1], box1.getRigidbody().getRotation(), box1.getRigidbody().getPosition());
		rotateVector2f(&axes[2], box2.getRigidbody().getRotation(), box2.getRigidbody().getPosition());
		rotateVector2f(&axes[3], box2.getRigidbody().getRotation(), box2.getRigidbody().getPosition());

		for (auto& axis : axes) {
			if (!overlapOnAxis(box1, box2, axis)) return false;
		}

		return true;
	}


	// ===============================
	// Separating Axis Theorem Helpers
	// ===============================

	//Checks if two AABB's overlap on the given axis 
	//NOTE: Axis must be normalized
	bool overlapOnAxis(AABB aabb1, AABB aabb2, Vector2f axis) {
		Vector2f interval1 = getInterval(aabb1, axis);
		Vector2f interval2 = getInterval(aabb2, axis);

		if (floatLT(interval1.x, interval2.y) && floatLT(interval2.x, interval1.y)) return true;

		return false;
	}

	//Checks if an AABB and Box overlap on the given axis 
	//NOTE: Axis must be normalized
	bool overlapOnAxis(AABB aabb, Box box, Vector2f axis) {
		Vector2f interval1 = getInterval(aabb, axis);
		Vector2f interval2 = getInterval(box, axis);

		if (floatLT(interval1.x, interval2.y) && floatLT(interval2.x, interval1.y)) return true;

		return false;
	}

	//Checks if two Box's overlap on the given axis 
	//NOTE: Axis must be normalized
	bool overlapOnAxis(Box box1, Box box2, Vector2f axis) {
		Vector2f interval1 = getInterval(box1, axis);
		Vector2f interval2 = getInterval(box2, axis);

		if (floatLT(interval1.x, interval2.y) && floatLT(interval2.x, interval1.y)) return true;

		return false;
	}

	//Gets the minimum and maximum points of an AABB projected onto the given axis
	//NOTE: Axis must be normalized
	Vector2f getInterval(AABB aabb, Vector2f axis) {
		Vector2f result; // result.x = min of interval, result.y = max of interval
		std::vector<Vector2f> vertices = aabb.getVertices();

		result.x = vDot(vertices[0], axis);
		result.y = result.x;

		for (int i = 1; i < 4; i++) {
			float projection = vDot(vertices[i], axis);
			if (floatLT(projection, result.x)) result.x = projection;
			else if (floatGT(projection, result.y)) result.y = projection;
		}

		return result;
	}

	//Gets the minimum and maximum points of a Box projected onto the given axis
	//NOTE: Axis must be normalized
	Vector2f getInterval(Box box, Vector2f axis) {
		Vector2f result; // result.x = min of interval, result.y = max of interval
		std::vector<Vector2f> vertices = box.getVertices();

		result.x = vDot(vertices[0], axis);
		result.y = result.x;

		for (int i = 1; i < 4; i++) {
			float projection = vDot(vertices[i], axis);
			if (floatLT(projection, result.x)) result.x = projection;
			else if (floatGT(projection, result.y)) result.y = projection;
		}

		return result;
	}
};