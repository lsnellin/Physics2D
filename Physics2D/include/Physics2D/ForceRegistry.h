#pragma once

#include "ForceRegistration.h"

namespace Physics2D {
	class ForceRegistry {
	private:
		std::vector<ForceRegistration*> registry;
	public:
		ForceRegistry();
		void add(Physics2D::ForceGenerator* fg, Physics2D::Rigidbody2D* rb);
		void add(Physics2D::ForceRegistration* fr);
		void remove(Physics2D::ForceRegistration* fr);
		void clear();
		void updateForces(float dt);
	};
}