#pragma once
#include <SFML/Graphics.hpp>
//====================================================
// Interface that must be implemented by collidable objects
//====================================================

namespace Physics2D {

	// Enum for specifying the type of Collider
	enum class Type {Collider2D, Circle, AABB, Box};

	class Collider2D {
	protected:
		sf::Vector2f offset;

	public:
		virtual Type getType() = 0;
	};

}

