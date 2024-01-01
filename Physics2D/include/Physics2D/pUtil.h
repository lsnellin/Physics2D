#pragma once

#include <cmath>
#include <SFML/Graphics.hpp>
#include <algorithm>

namespace Physics2D {
	bool floatCompare(float x, float y);
	bool compareVector2f(sf::Vector2f v1, sf::Vector2f v2);
	bool floatLT(float x, float y); // x < y
	bool floatGT(float x, float y); // x > y
	void rotateVector2f(sf::Vector2f* vec, float angleDegrees, sf::Vector2f origin);
}