#include "PhysicsTest.h"

using std::cout;
using std::string;
using std::endl;
using std::sqrt;
using std::vector;
using namespace Physics2D;
using namespace sf;

int main() {
	//runBackgroundTests();

	//fluidSim();
	manyBalls(25, 25, 4.f);
	//testPhysicsWorld();
	//visualizeRaycastBox();
	//visualizeCircleVSCircle();
	//visualizeCircleVSBox();
	
	return 0;
}
void manyBalls(int ballsX, int ballsY, float ballRadius) {

	Vector2f windowSize = Vector2f(1920, 1080);
	RenderWindow window(VideoMode(windowSize.x, windowSize.y), "MyGame");
	window.setFramerateLimit(60);
	Event event;

	//Define background:
	sf::RectangleShape background(windowSize);
	background.setFillColor(Color(0, 0, 0));

	//Define Physics:
	PhysicsSystem2D world = PhysicsSystem2D(.5f, Vector2f(0.f, 0.f));
	Vector2f worldCenter = windowSize / 2.f;

	// Create balls:
	vector<Circle*> particles;
	for (int i = 0; i < ballsX; i++) {
		for (int j = 0; j < ballsY; j++) {
			float centerX = (windowSize.x / 4) + (windowSize.x * i) / (2 * ballsX);
			float centerY = (windowSize.y / 4) + (windowSize.y * j) / (2 * ballsY);
			Vector2f ballCenter = Vector2f(centerX, centerY);
			Circle* particle = new Circle(ballRadius, ballCenter);
			//particle->getRigidbody()->setCor(0.75);

			// Generate Rotational Velocity about the center of screen:
			Vector2f distance = ballCenter - worldCenter;
			vNormalize(distance);
			rotateVector2f(distance, 90, Vector2f(0.f,0.f));
			particle->getRigidbody()->addLinearVelocity(distance * 5.f);

			// Generate a random color
			particle->setFillColor(
				Color((sf::Uint8)std::rand() % 256, (sf::Uint8)std::rand() % 256, (sf::Uint8)std::rand() % 256)
			);

			particles.push_back(particle);
			world.addRigidbody(particle->getRigidbody());
		}
	}

	

	//Initialize refresh rate:
	Clock clock = Clock();
	Time dt = seconds(1.f/60.f);

	//Main Game Loop:
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
		}

		//Update Physics

		for (int i = 0; i < particles.size(); i++) {
			Circle* p1 = particles[i];
			Vector2f distance = p1->getRigidbody()->getPosition() - worldCenter;
			vNormalize(distance);

			p1->getRigidbody()->addLinearVelocity(-1.f * distance);
		}

		world.fixedUpdate();

		window.draw(background);

		// Calculate positions and draw particles:
		for (Circle* particle : particles) {
			particle->updateFromRigidbody();
			window.draw(*particle);
		}

		if (clock.getElapsedTime() < dt) {
			sleep(dt - clock.getElapsedTime());
		}
		clock.restart();

		window.display();
		

	}
}

void testPhysicsWorld() {

	Vector2f windowSize = Vector2f(1920, 1080);
	RenderWindow window(VideoMode(windowSize.x, windowSize.y), "MyGame");
	window.setFramerateLimit(60);
	Event event;

	//Define background:
	sf::RectangleShape background(windowSize);
	background.setFillColor(Color(200, 200, 200));

	//Define Physics:
	PhysicsSystem2D world = PhysicsSystem2D(.1, Vector2f(0.f, 1.5f));

	Box b = Box(Vector2f(0.f, 0.f), Vector2f(100.f, 100.f));
	b.setFillColor(Color(155, 155, 0));
	b.setCenter(windowSize / 4.f);
	b.rotate(40.f);

	AABB ab2 = AABB(Vector2f(0.f,0.f), Vector2f(100.f,100.f));
	ab2.setFillColor(Color(155, 0, 155));
	ab2.setCenter(windowSize / 2.f);

	world.addRigidbody(b.getRigidbody());
	world.addRigidbody(ab2.getRigidbody());

	//Main Game Loop:
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}

			if (event.type == Event::KeyPressed) {
				if (event.key.scancode == Keyboard::Scan::Up) {
					b.getRigidbody()->addLinearVelocity(Vector2f(0.f, -25.f));
				}
				else if (event.key.scancode == Keyboard::Scan::Right) {
					b.getRigidbody()->addLinearVelocity(Vector2f(25.f, 0.f));
				}
				else if (event.key.scancode == Keyboard::Scan::Down) {
					b.getRigidbody()->addLinearVelocity(Vector2f(0.f, 25.f));
				}
				else if (event.key.scancode == Keyboard::Scan::Left) {
					b.getRigidbody()->addLinearVelocity(Vector2f(-25.f, 0.f));
				}

				else if (event.key.scancode == Keyboard::Scan::W) {
					ab2.getRigidbody()->addLinearVelocity(Vector2f(0.f, -25.f));
				}
				else if (event.key.scancode == Keyboard::Scan::D) {
					ab2.getRigidbody()->addLinearVelocity(Vector2f(25.f, 0.f));
				}
				else if (event.key.scancode == Keyboard::Scan::S) {
					ab2.getRigidbody()->addLinearVelocity(Vector2f(0.f, 25.f));
				}
				else if (event.key.scancode == Keyboard::Scan::A) {
					ab2.getRigidbody()->addLinearVelocity(Vector2f(-25.f, 0.f));
				}
				else if (event.key.scancode == Keyboard::Scan::Space) {
					b.setCenter(windowSize / 2.f);
					b.getRigidbody()->addLinearVelocity(-1.f * b.getRigidbody()->getLinearVelocity());

					ab2.setCenter(windowSize / 2.f + Vector2f(0.f, -windowSize.y / 4.f));
					ab2.getRigidbody()->addLinearVelocity(-1.f * ab2.getRigidbody()->getLinearVelocity());
				}
			}
		}
		//Update Physics
		world.fixedUpdate();
		b.updateFromRigidbody();
		ab2.updateFromRigidbody();
		//objectList.updateObjectList();
		window.draw(background);
		window.draw(b);
		window.draw(ab2);
		window.display();	

	}
}

void visualizeCircleVSBox() {
	Vector2f windowSize = Vector2f(1920, 1080);
	RenderWindow window(VideoMode(windowSize.x, windowSize.y), "MyGame");
	window.setFramerateLimit(60);
	Event event;

	//Define background:
	sf::RectangleShape background(windowSize);
	background.setFillColor(Color(0, 0, 0));

	//Define Circle1 (SFML)
	CircleShape circle;
	float radius1 = 128.f;
	float dx1 = 1.f;
	float dr1 = 2.f;
	circle.setRadius(radius1);
	circle.setOrigin(radius1, radius1);
	circle.setPosition(windowSize.x / 2, windowSize.y / 2);
	circle.setFillColor(Color::Transparent);
	circle.setOutlineColor(Color(175, 0, 175));
	circle.setOutlineThickness(2.f);

	//Define Box (SFML):
	RectangleShape box;
	float sideLength = 100.f;
	float dx2 = 2.5f;
	float rotationStep = 2.f;
	Vector2f boxSize(sideLength, sideLength);
	box.setSize(boxSize);
	box.setOrigin(sideLength / 2, sideLength / 2);
	box.setPosition(windowSize.x / 2, windowSize.y / 2);
	box.setFillColor(Color::Transparent);
	box.setOutlineColor(Color(175, 0, 175));
	box.setOutlineThickness(2.f);

	//Define circle for physics:
	Circle pCircle = Circle(radius1, Vector2f(windowSize.x / 2, windowSize.y / 2));
	float maxX = windowSize.x / 2 + 250;
	float minX = windowSize.x / 2 - 250;
	float maxR = 200.f;
	float minR = 50.f;

	//Define box for physics:
	Box pBox = Box(Vector2f(0, 0), boxSize);
	pBox.setCenter(windowSize / 2.f);

	//Main Game Loop:
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
		}

		//Update SFML Shapes and Physics:
		pCircle.setCenter(pCircle.getCenter() + Vector2f(dx1, 0.f));
		circle.setPosition(circle.getPosition() + Vector2f(dx1, 0.f));
		if (floatGT(pCircle.getCenter().x + dx1, maxX) || floatLT(pCircle.getCenter().x + dx1, minX)) {
			dx1 *= -1.f;
		}

		pCircle.setRadius(pCircle.getRadius() + dr1);
		circle.setRadius(circle.getRadius() + dr1);
		circle.setOrigin(circle.getRadius(), circle.getRadius());
		if (floatGT(pCircle.getRadius() + dr1, maxR) || floatLT(pCircle.getRadius() + dr1, minR)) {
			dr1 *= -1.f;
		}

		pBox.setCenter(pBox.getRigidbody()->getPosition() + Vector2f(dx2, 0.f));
		box.setPosition(box.getPosition() + Vector2f(dx2, 0.f));
		if (floatGT(pBox.getRigidbody()->getPosition().x + dx2, maxX) ||
			floatLT(pBox.getRigidbody()->getPosition().x + dx2, minX)) {
			dx2 *= -1.f;
		}

		box.rotate(rotationStep);
		pBox.rotate(-rotationStep);

		

		//Update colors for intersection detection
		if (circleVSBox(pCircle, pBox)) {
			circle.setOutlineColor(Color(255, 255, 0));
			box.setOutlineColor(Color(255, 255, 0));
		}
		else {
			circle.setOutlineColor(Color(175, 0, 175));
			box.setOutlineColor(Color(175, 0, 175));
		}

		window.draw(background);
		window.draw(box);
		window.draw(circle);
		window.display();

	}

}

void visualizeCircleVSCircle() {
	Vector2f windowSize = Vector2f(1920, 1080);
	RenderWindow window(VideoMode(windowSize.x, windowSize.y), "MyGame");
	window.setFramerateLimit(60);
	Event event;

	//Define background:
	sf::RectangleShape background(windowSize);
	background.setFillColor(Color(0, 0, 0));

	//Define Circle1 (SFML)
	CircleShape circle1;
	float radius1 = 128.f;
	float dx1 = 1.f;
	float dr1 = 2.f;
	circle1.setRadius(radius1);
	circle1.setOrigin(radius1, radius1);
	circle1.setPosition(windowSize.x / 2, windowSize.y / 2);
	circle1.setFillColor(Color::Transparent);
	circle1.setOutlineColor(Color(175, 0, 175));
	circle1.setOutlineThickness(2.f);

	//Define Circle2 (SFML)
	CircleShape circle2;
	float radius2 = 128.f;
	float dx2 = -1.f;
	float dr2 = -3.f;
	circle2.setRadius(radius2);
	circle2.setOrigin(radius2, radius2);
	circle2.setPosition(windowSize.x / 2, windowSize.y / 2);
	circle2.setFillColor(Color::Transparent);
	circle2.setOutlineColor(Color(175, 0, 175));
	circle2.setOutlineThickness(2.f);

	//Define circle for physics:
	Circle pCircle1 = Circle(radius1, Vector2f(windowSize.x / 2, windowSize.y / 2));
	Circle pCircle2 = Circle(radius2, Vector2f(windowSize.x / 2, windowSize.y / 2));
	float maxX = windowSize.x / 2 + 250;
	float minX = windowSize.x / 2 - 250;
	float maxR = 200.f;
	float minR = 50.f;

	//Main Game Loop:
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
		}

		//Update Circles and Physics:
		pCircle1.setCenter(pCircle1.getCenter() + Vector2f(dx1, 0.f));
		circle1.setPosition(circle1.getPosition() + Vector2f(dx1, 0.f));
		if (floatGT(pCircle1.getCenter().x + dx1, maxX) || floatLT(pCircle1.getCenter().x + dx1, minX)) {
			dx1 *= -1.f;
		}

		pCircle1.setRadius(pCircle1.getRadius() + dr1);
		circle1.setRadius(circle1.getRadius() + dr1);
		circle1.setOrigin(circle1.getRadius(), circle1.getRadius());
		if (floatGT(pCircle1.getRadius() + dr1, maxR) || floatLT(pCircle1.getRadius() + dr1, minR)) {
			dr1 *= -1.f;
		}

		pCircle2.setCenter(pCircle2.getCenter() + Vector2f(dx2, 0.f));
		circle2.setPosition(circle2.getPosition() + Vector2f(dx2, 0.f));
		if (floatGT(pCircle2.getCenter().x + dx2, maxX) || floatLT(pCircle2.getCenter().x + dx2, minX)) {
			dx2 *= -1.f;
		}

		pCircle2.setRadius(pCircle2.getRadius() + dr2);
		circle2.setRadius(circle2.getRadius() + dr2);
		circle2.setOrigin(circle2.getRadius(), circle2.getRadius());
		if (floatGT(pCircle2.getRadius() + dr2, maxR) || floatLT(pCircle2.getRadius() + dr2, minR)) {
			dr2 *= -1.f;
		}

		//Update colors for intersection detection
		if (circleVSCircle(pCircle1, pCircle2)) {
			circle1.setOutlineColor(Color(255, 255, 0));
			circle2.setOutlineColor(Color(255, 255, 0));
		}
		else {
			circle1.setOutlineColor(Color(175, 0, 175));
			circle2.setOutlineColor(Color(175, 0, 175));
		}

		window.draw(background);
		window.draw(circle1);
		window.draw(circle2);
		window.display();

	}

}

void visualizeRaycastBox() {
	Vector2f windowSize = Vector2f(1920, 1080);
	RenderWindow window(VideoMode(windowSize.x, windowSize.y), "MyGame");
	window.setFramerateLimit(144);
	Event event;

	//Define background:
	sf::RectangleShape background(windowSize);
	background.setFillColor(Color(0, 0, 0));

	//Define AABB (SFML)
	Vector2f rectSize(250.f, 320.f);
	Vector2f rectOrigin(windowSize.x / 2 - rectSize.x / 2, windowSize.y / 2 - rectSize.y / 2);
	sf::RectangleShape rect(rectSize);
	rect.setOutlineColor(Color(175, 0, 175));
	rect.setOutlineThickness(2.f);
	rect.setFillColor(Color(50, 50, 50));
	rect.setOrigin(rectSize.x / 2, rectSize.y / 2);
	rect.setPosition(windowSize.x / 2, windowSize.y / 2);

	Box box = Box(rectOrigin, rectOrigin + rectSize);

	//Define Ray:
	float maxDist = 100.f;
	float minDist = 50.f;
	float dist1 = 0.f; //Differential for point 1
	float dist2 = 0.f; //Differential for point 2
	float d1 = 2;
	float d2 = 4;
	Vector2f sizeMax(maxDist * 2 + rectSize.x, maxDist * 2 + rectSize.y); //point 1 bounding box
	Vector2f sizeMin(minDist * 2 + rectSize.x, minDist * 2 + rectSize.y); //point 2 bounding box
	Vector2f point1(rectOrigin.x - maxDist, rectOrigin.y - maxDist);
	Vector2f point2(rectOrigin.x - minDist, rectOrigin.y - minDist);
	Vector2f direction(point2 - point1);
	vNormalize(direction);
	sf::Vertex rayLine[] = { Vertex(point1), Vertex(point2) };
	Ray ray = Ray(point1, direction);
	RaycastResult result;

	//Define intersection:
	sf::CircleShape intersectPoint;
	float radius = 4.f;
	intersectPoint.setRadius(radius);
	intersectPoint.setFillColor(Color(255, 255, 0));
	intersectPoint.setPosition(5, 5);
	bool isIntersect = false;

	//Main Game Loop:
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
		}

		//Rotate Shapes:
		rect.rotate(-.5);
		box.rotate(.5);

		//Update rays:
		//Increase differentials:
		dist1 += d1;
		dist2 += d2;
		//Update point 1:
		if (dist1 <= sizeMax.x) point1.x += d1;
		else if (dist1 <= sizeMax.x + sizeMax.y) point1.y += d1;
		else if (dist1 <= sizeMax.x * 2 + sizeMax.y) point1.x -= d1;
		else if (dist1 <= sizeMax.x * 2 + sizeMax.y * 2) point1.y -= d1;
		else dist1 = 0;
		//Update point 2:
		if (dist2 <= sizeMin.x) point2.x += d2;
		else if (dist2 <= sizeMin.x + sizeMin.y) point2.y += d2;
		else if (dist2 <= sizeMin.x * 2 + sizeMin.y) point2.x -= d2;
		else if (dist2 <= sizeMin.x * 2 + sizeMin.y * 2) point2.y -= d2;
		else dist2 = 0;

		//Update raycast:
		direction = point2 - point1;
		vNormalize(direction);
		ray = Ray(point1, direction);
		raycast(box, ray, result);

		rayLine[0] = Vertex(point1);
		float t = result.getT();
		if (!floatLT(t, 0.f)) {
			isIntersect = true;
			intersectPoint.setPosition(result.getPoint().x - radius, result.getPoint().y - radius);
			if (vLengthSquared(result.getPoint() - point1) <= vLengthSquared(point2 - point1)) {
				rayLine[1] = Vertex(result.getPoint());
			}
			else {
				rayLine[1] = Vertex(point2);
			}
		}
		else {
			isIntersect = false;
			rayLine[1] = Vertex(point2);
		}


		window.draw(background);
		window.draw(rect);
		window.draw(rayLine, 2, sf::Lines);
		if (isIntersect) window.draw(intersectPoint);
		window.display();

	}
}

void runBackgroundTests() {
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
	//Test raycast AABB:
	cout << "Raycast AABB:          " << (testRaycastAABB() ? pass : fail) << endl;
	//Test raycast Box:
	cout << "Raycast Box:           " << (testRaycastBox() ? pass : fail) << endl;
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
	Circle* circle = new Circle(2.0f, Vector2f(0.f,0.f));
	Vector2f point = Vector2f(1.0f, 1.0f);
	if (!pointInCircle(point, *circle)) {
		delete circle;
		return false;
	}
	delete circle;


	//Test case 2: Circle r = 2, center = (4,3) contains point (4,1) (EDGE CASE):
	circle = new Circle(2.0f, Vector2f(4.f, 3.f));
	point = Vector2f(4.0f, 1.0f);
	if (!pointInCircle(point, *circle)) {
		delete circle;
		return false;
	}

	//Test case 3: Circle r = 2, center = (4,3) doesn't contain point (0,0):
	point = Vector2f(0.0f, 0.0f);
	if (pointInCircle(point, *circle)) {
		delete circle;
		return false;
	}

	delete circle;
	return true;
}

bool testPointInAABB() {
	//Test case 1: Point (1,1) and AABB{ (0,0) (2,2) } should return true:
	AABB* aabb = new AABB(Vector2f(0.f, 0.f), Vector2f(2.0f, 2.0f));
	Vector2f point = Vector2f(1.0f, 1.0f);
	if (!pointInAABB(point, *aabb)) {
		delete aabb;
		return false;
	}

	//Test case 2: Point (2,2) and AABB{ (0,0) (2,2) } should return true:
	point = Vector2f(2.f, 2.f);
	if (!pointInAABB(point, *aabb)) {
		delete aabb;
		return false;
	}

	//Test case 3: Point (2.01, 2) and AABB{ (0,0) (2,2) } should return false:
	point = Vector2f(2.01f, 2.0f);
	if (pointInAABB(point, *aabb)) {
		delete aabb;
		return false;
	}

	delete aabb;
	return true;

}

bool testPointInBox() {
	Box* box = new Box(Vector2f(0.f, 0.f), Vector2f(8.f, 4.f));
	box->rotate(90);

	//Test case 1: point (4, 2) is in box:
	Vector2f point = Vector2f(4.f, 2.f);
	if (!pointInBox(point, *box)) {
		delete box;
		return false;
	}
	//Test case 2: point (2, 2) is in box:
	point = Vector2f(2.f, 2.f);
	if (!pointInBox(point, *box)) {
		delete box;
		return false;
	}

	//Test case 3: point (-1, -1) is not in box:
	point = Vector2f(-1.f, -1.f);
	if (pointInBox(point, *box)) {
		delete box;
		return false;
	}

	delete box;
	return true;
}

bool testRotateVector2f() {
	//Test 1: Rotate (0, 0) around (-1, -1) by 180 degrees
	Vector2f vec = Vector2f(0.0f, 0.0f);
	float angleDegrees = 180.f;
	Vector2f origin = Vector2f(-1.f, -1.f);
	Vector2f expectedAnswer = Vector2f(-2.0f, -2.0f);
	rotateVector2f(vec, angleDegrees, origin);
	if (!compareVector2f(vec, expectedAnswer)) return false;

	//Test 2: Rotate (2, 2) around (2, 2)
	vec = Vector2f(2.0f, 2.0f);
	angleDegrees = 200.f;
	origin = Vector2f(vec);
	expectedAnswer = Vector2f(vec);
	rotateVector2f(vec, angleDegrees, origin);
	if (!compareVector2f(vec, expectedAnswer)) return false;

	//Test 3: Rotate (5, 0) around (0, 0) -270 degrees:
	vec = Vector2f(5.0f, 0.0f);
	angleDegrees = -270.f;
	origin = Vector2f(0.f, 0.f);
	expectedAnswer = Vector2f(0.f, 5.f);
	rotateVector2f(vec, angleDegrees, origin);
	if (!compareVector2f(vec, expectedAnswer)) return false;

	return true;
}

bool testLineVSCircle() {
	//Circle with radius 2 and origin 0
	Circle* circle = new Circle(2.0f, Vector2f(0.f, 0.f));
	
	//Test case 1: line from (-1, 1) to (1, 1) should intersect circle:
	Line* line = new Line(Vector2f(-1.f, 1.f), Vector2f(1.f, 1.f));
	if (!lineVSCircle(*line, *circle)) {
		delete circle;
		delete line;
		return false;
	}

	//Test case 2: line from (-2, 2) to (2, 2) should intersect circle:
	delete line;
	line = new Line(Vector2f(-2.f, 1.f), Vector2f(2.f, 1.f));
	if (!lineVSCircle(*line, *circle)) {
		delete circle;
		delete line;
		return false;
	}

	//Test case 3: line from (2, 1) to (4, 1) should not intersect circle:
	delete line;
	line = new Line(Vector2f(2.f, 1.f), Vector2f(4.f, 1.f));
	if (lineVSCircle(*line, *circle)) {
		delete circle;
		delete line;
		return false;
	}

	delete circle;
	delete line;
	return true;
}

bool testLineVSAABB() {

	//Test case 1: AABB [ (1,1) (3,3) ] should intersect with line (-10,-10)->(10,10)
	Line* line = new Line(Vector2f(-10.f, -10.f), Vector2f(10.f, 10.f));
	AABB* aabb = new AABB(Vector2f(1.f, 1.f), Vector2f(3.f, 3.f));
	if (!lineVSAABB(*line, *aabb)) {
		delete aabb;;
		delete line;
		return false;
	}

	//Test case 2: Same AABB should intersect with line from (1,1)->(-1,-1)
	delete line;
	line = new Line(Vector2f(1.f, 1.f), Vector2f(-1.f, -1.f));
	if (!lineVSAABB(*line, *aabb)) {
		delete aabb;;
		delete line;
		return false;
	}

	//Test case 3: Same AABB should intersect with line from (0,2)->(2,0):
	delete line;
	line = new Line(Vector2f(0.f, 2.f), Vector2f(2.f, 0.f));
	if (!lineVSAABB(*line, *aabb)) {
		delete aabb;;
		delete line;
		return false;
	}

	//Test case 4: Same AABB should NOT intersect with line from (0, 1.9)->(2,0)
	delete line;
	line = new Line(Vector2f(0.f, 1.9f), Vector2f(2.f, 0.f));
	if (lineVSAABB(*line, *aabb)) {
		delete line;
		delete aabb;;
		return false;
	}

	//Test passed
	delete aabb;;
	delete line;
	return true;

}

bool testLineVSBox() {
	//Test case 1: Box [ (0,0) (2,2) ] rotated 45 degrees intersects with line from (-5,-.25)->(5,-.25):
	Line* line = new Line(Vector2f(-5.f, -0.25f), Vector2f(5.f, -0.25f));
	Box* box = new Box(Vector2f(0.f, 0.f), Vector2f(2.f,2.f));
	box->rotate(45.f);
	if (!lineVSBox(*line, *box)) {
		delete box;
		delete line;
		return false;
	}

	//Test case 2: Line is inside of box:
	line = new Line(Vector2f(.5f, .5f), Vector2f(1.5f, 1.5f));
	if (!lineVSBox(*line, *box)) {
		delete box;
		delete line;
		return false;
	}

	//Test case 3: Line intersects with box at exactly one corner:
	float cornerY = 1.f - (2.f / sqrt(2));
	line = new Line(Vector2f(-5.f, cornerY), Vector2f(5.f, cornerY));
	if (!lineVSBox(*line, *box)) {
		delete box;
		delete line;
		return false;
	}

	//Test case 4: Shouldn't intersect with line from (-5,-5)->(-1,-1)
	line = new Line(Vector2f(-5.f, -5.f), Vector2f(-1.f, -1.f));
	if (lineVSBox(*line, *box)) {
		delete box;
		delete line;
		return false;
	}

	//Test case 5: Shouldn't intersect with line from (-5,-.5)->(5,-.5):
	line = new Line(Vector2f(-5.f, -0.5f), Vector2f(5.f, -0.5f));
	if (lineVSBox(*line, *box)) {
		delete box;
		delete line;
		return false;
	}

	//Test case 6: Rotate the box 45 more degrees and it shouldn't intersect with line (-5,-.25)->(5,-.25):
	line = new Line(Vector2f(-5.f, -0.25f), Vector2f(5.f, -0.25f));
	box->rotate(45.f);
	if (lineVSBox(*line, *box)) {
		delete box;
		delete line;
		return false;
	}

	//Test passed
	delete box;
	delete line;
	return true;
}

bool testRaycastCircle() {
	//Test Case 1: Ray starts outside circle and hits circle:
	Circle* circle = new Circle(2.f, Vector2f(4.f, 4.f));
	Vector2f origin(0.f, 0.f);
	Vector2f expectedPoint(4.f, 2.f);
	Vector2f dir = expectedPoint - origin;
	Vector2f expectedNormal = expectedPoint - circle->getCenter();
	vNormalize(expectedNormal);
	vNormalize(dir);
	Ray ray = Ray(origin, dir);
	RaycastResult result = RaycastResult();

	if (!raycast(*circle, ray, result)) {
		delete circle;
		return false; //Ensure ray hits:
	}

	//Ensure properties are as expected:
	if (!compareVector2f(result.getPoint(), expectedPoint, 0.0001f)) {
		delete circle;
		return false;
	}
	if (!compareVector2f(result.getNormal(), expectedNormal, 0.0001f)) {
		delete circle;
		return false;
	}

	//Test Case 2: Ray starts inside the circle:
	origin = Vector2f(3.f, 3.f);
	expectedPoint = Vector2f(6.f, 4.f);
	dir = expectedPoint - origin;
	expectedNormal = expectedPoint - circle->getCenter();
	vNormalize(expectedNormal);
	vNormalize(dir);
	ray = Ray(origin, dir);

	if (!raycast(*circle, ray, result)) {
		delete circle;
		return false; //Ensure ray hits:
	}

	//Ensure properties are as expected:
	if (!compareVector2f(result.getPoint(), expectedPoint, 0.0001f)) {
		delete circle;
		return false;
	}
	if (!compareVector2f(result.getNormal(), expectedNormal, 0.0001f)) {
		delete circle;
		return false;
	}

	//Test Case 3: Ray starts outside circle and doesn't hit:
	origin = Vector2f(1.99f, 1.f);
	dir = Vector2f(0.f, 1.f);
	ray = Ray(origin, dir);

	if (raycast(*circle, ray, result)) {
		delete circle;
		return false; //Ensure ray doesn't hit:
	}

	//Test passed
	delete circle;
	return true;
}

bool testRaycastAABB() {
	//Test case 1: AABB from (0,0) (2,2) and Ray (-1,0) direction (1,0)
	RaycastResult result = RaycastResult();
	Vector2f origin(-1.f, 1.f);
	Vector2f dir(1.f, 0.f);
	Vector2f expectedPoint(0.f,1.f);
	Vector2f expectedNormal = dir * -1.f;
	Ray ray = Ray(origin, dir);
	AABB* aabb = new AABB(Vector2f(0.f, 0.f), Vector2f(2.f, 2.f));

	//Cast ray
	if (!raycast(*aabb, ray, result)) {
		delete aabb;
		return false;
	}
	//Ensure properties are as expected:
	if (!compareVector2f(result.getPoint(), expectedPoint, 0.0001f)) {
		delete aabb;
		return false;
	}
	if (!compareVector2f(result.getNormal(), expectedNormal, 0.0001f)) {
		delete aabb;
		return false;
	}

	//Test case 2: AABB from (0,0) (2,2) and Ray (1,1) direction (1,0)
	origin = Vector2f(1.f, 1.f);
	dir = Vector2f(1.f, 0.f);
	expectedPoint = Vector2f(2.f, 1.f);
	expectedNormal = dir * -1.f;
	ray = Ray(origin, dir);

	//Cast ray
	if (!raycast(*aabb, ray, result)) {
		delete aabb;
		return false;
	}
	//Ensure properties are as expected:
	if (!compareVector2f(result.getPoint(), expectedPoint, 0.0001f)) {
		delete aabb;
		return false;
	}
	if (!compareVector2f(result.getNormal(), expectedNormal, 0.0001f)) {
		delete aabb;
		return false;
	}

	//Test passed
	delete aabb;
	return true;
}

bool testRaycastBox() {
	//Test passed
	return true;
}