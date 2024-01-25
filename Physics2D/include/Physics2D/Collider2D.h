#pragma once
#include "Collider2D.h"
#include <SFML/Graphics.hpp>


namespace Physics2D {
	enum class Type {Collider2D, Circle, AABB, Box};

	class Collider2D {
	protected:
		sf::Vector2f offset;

	public:
		virtual Type getType() = 0;
	};

}

