#pragma once

#include <SFML/Graphics.hpp>

class Line {
private:
	sf::Vector2f start;
	sf::Vector2f end;
public:
	sf::Vector2f getStart();
	sf::Vector2f getEnd();
};