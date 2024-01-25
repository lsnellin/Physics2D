#pragma once

#include "Rigidbody2D.h"

namespace Physics2D {
	class ForceGenerator {
	public:
		virtual void updateForce(Physics2D::Rigidbody2D& rb, float dt) = 0;
	};
}