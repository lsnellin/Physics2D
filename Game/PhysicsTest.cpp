#include "PhysicsTest.h"

using std::cout;
using std::string;
using std::sqrt;
using sf::Vector2f;
using namespace Physics2D;

int main() {
	const string pass = "PASS";
	const string fail = "FAIL";

	//Test pointOnLine:
	cout << "Point on Line:         " << (testPointOnLine() ? pass : fail) << endl;

	//Test pointInCircle:
	cout << "Point in Circle:       " << (testPointInCircle() ? pass : fail) << endl;

	//Test pointInAABB:
	cout << "Point in AABB:         " << (testPointInAABB() ? pass : fail) << endl;

	//Test pointInBox:
	cout << "Point in Box:          " << (testPointInBox() ? pass : fail) << endl;

	//Test rotateVector2f:
	cout << "Rotate Vector:         " << (testRotateVector2f() ? pass : fail) << endl;

	//Test lineIntersectCircle:
	cout << "Line VS Circle:        " << (testLineVSCircle() ? pass : fail) << endl;

	//Test lineVSAABB:
	cout << "Line VS AABB:          " << (testLineVSAABB() ? pass : fail) << endl;

	//Test lineVSBox:
	cout << "Line VS Box:           " << (testLineVSBox() ? pass : fail) << endl;

	//Test raycast circle:
	cout << "Raycast Circle:        " << (testRaycastCircle() ? pass : fail) << endl;

}

bool testPointOnLine() {
	// Y = 1/2X + 1
	Line line = Line(Vector2f(0.f, 1.f), Vector2f(4.0f, 3.0f));

	//Test case 1: point (6, 4) should be on line:
	Vector2f point(6.0f, 4.0f);
	if (!pointOnLine(point, line)) return false;

	//Test case 2: point (1,1) should not be on line:
	point = Vector2f(1.f, 1.f);
	if (pointOnLine(point, line)) return false;

	//Test passed
	return true;
}

bool testPointInCircle() {
	//Test case 1: Circle r = 2, center = (0,0) contains point (1,1):
	Circle circle = Circle(2.0f, Vector2f(0.f,0.f));
	Vector2f point = Vector2f(1.0f, 1.0f);
	if (!pointInCircle(point, circle)) return false;

	//Test case 2: Circle r = 2, center = (4,3) contains point (4,1) (EDGE CASE):
	circle = Circle(2.0f, Vector2f(4.f, 3.f));
	point = Vector2f(4.0f, 1.0f);
	if (!pointInCircle(point, circle)) return false;

	//Test case 3: Circle r = 2, center = (4,3) doesn't contain point (0,0):
	point = Vector2f(0.0f, 0.0f);
	if (pointInCircle(point, circle)) return false;

	return true;
}

bool testPointInAABB() {
	//Test case 1: Point (1,1) and AABB{ (0,0) (2,2) } should return true:
	AABB aabb = AABB(Vector2f(0.f, 0.f), Vector2f(2.0f, 2.0f));
	Vector2f point = Vector2f(1.0f, 1.0f);
	if (!pointInAABB(point, aabb)) return false;

	//Test case 2: Point (2,2) and AABB{ (0,0) (2,2) } should return true:
	point = Vector2f(2.f, 2.f);
	if (!pointInAABB(point, aabb)) return false;

	//Test case 3: Point (2.01, 2) and AABB{ (0,0) (2,2) } should return false:
	point = Vector2f(2.01f, 2.0f);
	if (pointInAABB(point, aabb)) return false;

	return true;

}

bool testPointInBox() {
	Box box = Box(Vector2f(0.f, 0.f), Vector2f(8.f, 4.f));
	box.rotate(90);

	//Test case 1: point (4, 2) is in box:
	Vector2f point = Vector2f(4.f, 2.f);
	if (!pointInBox(point, box)) return false;

	//Test case 2: point (2, 2) is in box:
	point = Vector2f(2.f, 2.f);
	if (!pointInBox(point, box)) return false;

	//Test case 3: point (-1, -1) is not in box:
	point = Vector2f(-1.f, -1.f);
	if (pointInBox(point, box)) return false;

	return true;
}

bool testRotateVector2f() {
	//Test 1: Rotate (0, 0) around (-1, -1) by 180 degrees
	Vector2f vec = Vector2f(0.0f, 0.0f);
	float angleDegrees = 180.f;
	Vector2f origin = Vector2f(-1.f, -1.f);
	Vector2f expectedAnswer = Vector2f(-2.0f, -2.0f);
	rotateVector2f(&vec, angleDegrees, origin);
	if (!compareVector2f(vec, expectedAnswer)) return false;

	//Test 2: Rotate (2, 2) around (2, 2)
	vec = Vector2f(2.0f, 2.0f);
	angleDegrees = 200.f;
	origin = Vector2f(vec);
	expectedAnswer = Vector2f(vec);
	rotateVector2f(&vec, angleDegrees, origin);
	if (!compareVector2f(vec, expectedAnswer)) return false;

	//Test 3: Rotate (5, 0) around (0, 0) -270 degrees:
	vec = Vector2f(5.0f, 0.0f);
	angleDegrees = -270.f;
	origin = Vector2f(0.f, 0.f);
	expectedAnswer = Vector2f(0.f, 5.f);
	rotateVector2f(&vec, angleDegrees, origin);
	if (!compareVector2f(vec, expectedAnswer)) return false;

	return true;
}

bool testLineVSCircle() {
	//Circle with radius 2 and origin 0
	Circle circle = Circle(2.0f, Vector2f(0.f, 0.f));
	
	//Test case 1: line from (-1, 1) to (1, 1) should intersect circle:
	Line line = Line(Vector2f(-1.f, 1.f), Vector2f(1.f, 1.f));
	if (!lineVSCircle(line, circle)) return false;

	//Test case 2: line from (-2, 2) to (2, 2) should intersect circle:
	line = Line(Vector2f(-2.f, 1.f), Vector2f(2.f, 1.f));
	if (!lineVSCircle(line, circle)) return false;

	//Test case 3: line from (2, 1) to (4, 1) should not intersect circle:
	line = Line(Vector2f(2.f, 1.f), Vector2f(4.f, 1.f));
	if (lineVSCircle(line, circle)) return false;


	return true;
}

bool testLineVSAABB() {

	//Test case 1: AABB [ (1,1) (3,3) ] should intersect with line (-10,-10)->(10,10)
	Line line = Line(Vector2f(-10.f, -10.f), Vector2f(10.f, 10.f));
	AABB aabb = AABB(Vector2f(1.f, 1.f), Vector2f(3.f, 3.f));
	if (!lineVSAABB(line, aabb)) return false;

	//Test case 2: Same AABB should intersect with line from (1,1)->(-1,-1)
	line = Line(Vector2f(1.f, 1.f), Vector2f(-1.f, -1.f));
	if (!lineVSAABB(line, aabb)) return false;

	//Test case 3: Same AABB should intersect with line from (0,2)->(2,0):
	line = Line(Vector2f(0.f, 2.f), Vector2f(2.f, 0.f));
	if (!lineVSAABB(line, aabb)) return false;

	//Test case 4: Same AABB should NOT intersect with line from (0, 1.9)->(2,0)
	line = Line(Vector2f(0.f, 1.9f), Vector2f(2.f, 0.f));
	if (lineVSAABB(line, aabb)) return false;

	//Test passed
	return true;

}

bool testLineVSBox() {
	//Test case 1: Box [ (0,0) (2,2) ] rotated 45 degrees intersects with line from (-5,-.25)->(5,-.25):
	Line line = Line(Vector2f(-5.f, -0.25f), Vector2f(5.f, -0.25f));
	Box box = Box(Vector2f(0.f, 0.f), Vector2f(2.f,2.f));
	box.rotate(45.f);
	if (!lineVSBox(line, box)) return false;

	//Test case 2: Line is inside of box:
	line = Line(Vector2f(.5f, .5f), Vector2f(1.5f, 1.5f));
	if (!lineVSBox(line, box)) return false;

	//Test case 3: Line intersects with box at exactly one corner:
	float cornerY = 1.f - (2.f / sqrt(2));
	line = Line(Vector2f(-5.f, cornerY), Vector2f(5.f, cornerY));
	if (!lineVSBox(line, box)) return false;

	//Test case 4: Shouldn't intersect with line from (-5,-5)->(-1,-1)
	line = Line(Vector2f(-5.f, -5.f), Vector2f(-1.f, -1.f));
	if (lineVSBox(line, box)) return false;

	//Test case 5: Shouldn't intersect with line from (-5,-.5)->(5,-.5):
	line = Line(Vector2f(-5.f, -0.5f), Vector2f(5.f, -0.5f));
	if (lineVSBox(line, box)) return false;

	//Test case 6: Rotate the box 45 more degrees and it shouldn't intersect with line (-5,-.25)->(5,-.25):
	line = Line(Vector2f(-5.f, -0.25f), Vector2f(5.f, -0.25f));
	box.rotate(45.f);
	if (lineVSBox(line, box)) return false;


	//Test passed
	return true;
}

bool testRaycastCircle() {
	//Test Case 1: Ray starts outside circle and hits circle:
	Circle circle = Circle(2.f, Vector2f(4.f, 4.f));
	Vector2f origin(0.f, 0.f);
	Vector2f expectedPoint(4.f, 2.f);
	Vector2f dir = expectedPoint - origin;
	Vector2f expectedNormal = expectedPoint - circle.getCenter();
	vNormalize(&expectedNormal);
	vNormalize(&dir);
	Ray ray = Ray(origin, dir);
	RaycastResult result = RaycastResult();

	if (!raycast(circle, ray, &result)) return false; //Ensure ray hits:

	//Ensure properties are as expected:
	if (!compareVector2f(result.getPoint(), expectedPoint, 0.0001f)) {
		return false;
	}
	if (!compareVector2f(result.getNormal(), expectedNormal, 0.0001f)) {
		return false;
	}

	//Test Case 2: Ray starts inside the circle:
	origin = Vector2f(3.f, 3.f);
	expectedPoint = Vector2f(6.f, 4.f);
	dir = expectedPoint - origin;
	expectedNormal = expectedPoint - circle.getCenter();
	vNormalize(&expectedNormal);
	vNormalize(&dir);
	ray = Ray(origin, dir);

	if (!raycast(circle, ray, &result)) return false; //Ensure ray hits:

	//Ensure properties are as expected:
	if (!compareVector2f(result.getPoint(), expectedPoint, 0.0001f)) {
		return false;
	}
	if (!compareVector2f(result.getNormal(), expectedNormal, 0.0001f)) {
		return false;
	}

	//Test Case 3: Ray starts outside circle and doesn't hit:
	origin = Vector2f(1.99f, 1.f);
	dir = Vector2f(0.f, 1.f);
	ray = Ray(origin, dir);

	if (raycast(circle, ray, &result)) return false; //Ensure ray doesn't hit:

	//Test passed
	return true;
}