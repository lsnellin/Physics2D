#pragma once

#include "ForceGenerator.h"

namespace Physics2D {
	class Gravity2D : public ForceGenerator {
	private:
		sf::Vector2f gravity;
	public:
		Gravity2D(sf::Vector2f force);
		void updateForce(Physics2D::Rigidbody2D * rb, float dt);
	};
}