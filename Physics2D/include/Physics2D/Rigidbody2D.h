#pragma once
#include <SFML/Graphics.hpp>
#include "pUtil.h"
#include "Collider2D.h"

namespace Physics2D {
	class Rigidbody2D {
	private:
		sf::Vector2f position;
		sf::Vector2f linearVelocity;
		sf::Vector2f forceAccumulator;
		Physics2D::Collider2D collider;
		float mass;
		float inverseMass;

		float rotation;
		float angularVelocity;
		float linearDamping;
		float angularDamping;
		bool fixedRotation;
		void clearAccumulators();
		void syncCollisionTransforms();


	public:
		Rigidbody2D();
		Rigidbody2D(sf::Vector2f position, float rotation);
		sf::Vector2f getPosition();
		float getRotation();
		float getMass();
		void setMass(float mass);
		void setPosition(sf::Vector2f position);
		void setRotation(float rotation);
		void setTransform(sf::Vector2f position, float rotation);
		void setTransform(sf::Vector2f position);
		void physicsUpdate(float dt);
		void addForce(sf::Vector2f force);
		void addLinearVelocity(sf::Vector2f velocity);
		sf::Vector2f getLinearVelocity();
		bool hasInfiniteMass();
		Physics2D::Collider2D getCollider();
	};
}