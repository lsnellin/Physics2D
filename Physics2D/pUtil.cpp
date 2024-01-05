#include "pUtil.h"

constexpr auto PI = 3.14159265358979323846;

namespace Physics2D {
	
	bool floatCompare(float x, float y) {
		//Check if x == y
		float max1XY = std::max(std::fabs(x), std::fabs(y));
		max1XY = std::max(max1XY, 1.0f);
		return std::fabs(x - y) <= max1XY * std::numeric_limits<float>::epsilon();
	}

	bool compareVector2f(sf::Vector2f v1, sf::Vector2f v2) {
		//Check if v1 == v2
		return Physics2D::floatCompare(v1.x, v2.x) && Physics2D::floatCompare(v1.y, v2.y);
	}

	bool floatLT(float x, float y) {
		//Check if x < y
		float max1XY = std::max(std::fabs(x), std::fabs(y));
		max1XY = std::max(max1XY, 1.0f);
		return (y - x) > max1XY * std::numeric_limits<float>::epsilon();
	}

	bool floatGT(float x, float y) {
		//Check if x > y
		float max1XY = std::max(std::fabs(x), std::fabs(y));
		max1XY = std::max(max1XY, 1.0f);
		return (x - y) > max1XY * std::numeric_limits<float>::epsilon();
	}

	void rotateVector2f(sf::Vector2f* vec, float angleDegrees, sf::Vector2f origin) {
		//Convert angle to radians:
		float radians = angleDegrees * PI / 180.f;
		//Move vector to origin:
		*vec -= origin;

		//Rotate moved vector:
		float newX = vec->x * std::cos(radians) - vec->y * std::sin(radians);
		float newY = vec->x * std::sin(radians) + vec->y * std::cos(radians);

		vec->x = newX;
		vec->y = newY;

		//Move vector back from origin
		*vec += origin;
	}
};
