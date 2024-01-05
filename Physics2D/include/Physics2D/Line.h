#pragma once

#include <SFML/Graphics.hpp>

namespace Physics2D {
	class Line 
	{
	private:
		sf::Vector2f start;
		sf::Vector2f end;
	public:
		Line();
		Line(sf::Vector2f start, sf::Vector2f end);
		sf::Vector2f getStart();
		sf::Vector2f getEnd();
		sf::Vector2f getVector();
	};
}