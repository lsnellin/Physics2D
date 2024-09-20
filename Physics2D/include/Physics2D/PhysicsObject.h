#pragma once
#include "Collider2D.h"
#include "RigidBody2D.h"

namespace Physics2D {
	class PhysicsObject {
	public:
		virtual void updateFromRigidbody() = 0;
		virtual Physics2D::Rigidbody2D* getRigidbody() = 0;
		virtual Physics2D::Type getType() = 0;
	};
}