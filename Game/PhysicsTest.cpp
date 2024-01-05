#include "PhysicsTest.h"

using std::cout;
using std::string;
using sf::Vector2;
using namespace Physics2D;

int main() {
	const string success = "SUCCESS";
	const string failed = "FAILED";
	//Test pointInCircle:
	cout << "Point in Circle: " << (testPointInCircle() ? success : failed) << endl;

	//Test pointInAABB:
	cout << "Point in AABB: " << (testPointInAABB() ? success : failed) << endl;

	//Test pointInBox:
	cout << "Point in Box: " << (testPointInBox() ? success : failed) << endl;

	//Test rotateVector2f:
	cout << "Rotate Vector: " << (testRotateVector2f() ? success : failed) << endl;

}

bool testPointInCircle() {
	bool testPass = true;

	//Check that point is in circle:
	Circle circle = Circle(2.0f);
	Vector2f point = Vector2f(1.0f, 1.0f);
	testPass = testPass && pointInCirlce(point, circle);

	//Check that point is not in circle:
	point = Vector2f(2.0f, 2.0f);
	testPass = testPass && !pointInCirlce(point, circle);

	return testPass;
}

bool testPointInAABB() {
	bool testPass = true;

	//Check that point is in AABB:
	AABB aabb = AABB(Vector2f(0.f, 0.f), Vector2f(2.0f, 2.0f));
	Vector2f point = Vector2f(1.0f, 1.0f);
	testPass = testPass && pointInAABB(point, aabb);

	//Check that point is NOT in AABB:
	point = Vector2f(3.0f, 2.0f);
	testPass = testPass && !pointInAABB(point, aabb);

	return testPass;

}

bool testPointInBox() {
	bool testPass = true;
	Box box = Box(Vector2f(0, 0), Vector2f(2, 1));
	box.rotate(90);

	//Make sure point is in box:
	Vector2f point = Vector2f(1.0f, 1.25f);
	testPass = testPass && pointInBox(point, box);

	//Make sure point is not in box:
	point = Vector2f(1.75f, 1.0f);
	testPass = testPass && !pointInBox(point, box);

	return testPass;
}

bool testRotateVector2f() {
	Vector2f vec = Vector2f(0.0f, 0.0f);
	float angleDegrees = 180.f;
	Vector2f origin = Vector2f(-1.f, -1.f);

	Vector2f expectedAnswer = Vector2f(-2.0f, -2.0f);
	rotateVector2f(&vec, angleDegrees, origin);

	return compareVector2f(vec, expectedAnswer);
}