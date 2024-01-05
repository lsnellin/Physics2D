#pragma once

#include <cmath>
#include <SFML/Graphics.hpp>
#include <algorithm>

namespace Physics2D {
	bool floatCompare(float x, float y);
	bool floatCompare(float x, float y, float epsilon);
	bool compareVector2f(sf::Vector2f v1, sf::Vector2f v2);
	bool compareVector2f(sf::Vector2f v1, sf::Vector2f v2, float epsilon);
	bool floatLT(float x, float y); // x < y
	bool floatGT(float x, float y); // x > y
	void rotateVector2f(sf::Vector2f* vec, float angleDegrees, sf::Vector2f origin);
	float vDot(sf::Vector2f v1, sf::Vector2f v2);
	float vLength(sf::Vector2f vec);
	float vLengthSquared(sf::Vector2f vec);
	void vNormalize(sf::Vector2f* vec);
	
}