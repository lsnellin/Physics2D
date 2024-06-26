#pragma once

#include "ForceRegistry.h"
#include "Gravity2D.h"
#include "CollisionManifold.h"
#include "Collisions.h"
#include "Collider2D.h"
#include "ObjectList.h"
#include <SFML/Graphics.hpp>

namespace Physics2D {
	class PhysicsSystem2D {
	private:
		Physics2D::ForceRegistry forceRegistry;
		std::vector<Physics2D::Rigidbody2D*> rigidbodies;
		std::vector<Physics2D::Rigidbody2D*> bodies1;
		std::vector<Physics2D::Rigidbody2D*> bodies2;
		std::vector<Physics2D::CollisionManifold> collisions;

		Physics2D::Gravity2D *gravity;
		float fixedUpdateDT;
		float impulseIterations;

	public:
		PhysicsSystem2D(float fixedUpdateDT, sf::Vector2f gravity);
		~PhysicsSystem2D();
		void update(float dt);
		void fixedUpdate();
		void addRigidbody(Physics2D::Rigidbody2D* rb);
		void applyImpulse(Physics2D::Rigidbody2D& rb1, Physics2D::Rigidbody2D& rb2, Physics2D::CollisionManifold m);
		void addObjectList(std::vector<Physics2D::PhysicsObject*> objects);
	};
}