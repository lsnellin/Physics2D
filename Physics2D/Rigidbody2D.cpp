#include "Rigidbody2D.h"

using namespace Physics2D;
using sf::Vector2f;

Rigidbody2D::Rigidbody2D(Collider2D* collider) :
	position(Vector2f()),
	rotation(0.0f),
	mass(1.f),
	inverseMass(1.f),

	forceAccumulator(Vector2f()),
	linearVelocity(Vector2f()),
	collider(collider),

	angularVelocity(0.f),
	linearDamping(0.f),
	angularDamping(0.f),
	cor(1.f),
	fixedRotation(false)
{
}

Rigidbody2D::Rigidbody2D(Vector2f position, float rotation, Collider2D* collider) :
	position(position),
	rotation(rotation),
	mass(1.f),
	inverseMass(1.f),

	forceAccumulator(Vector2f()),
	linearVelocity(Vector2f()),
	collider(collider),

	angularVelocity(0.f),
	linearDamping(0.f),
	angularDamping(0.f),
	cor(1.f),
	fixedRotation(false)
{
}

void Rigidbody2D::addLinearVelocity(Vector2f velocity) {
	this->linearVelocity += velocity;
}

Vector2f Rigidbody2D::getLinearVelocity() {
	return this->linearVelocity;
}

Vector2f Rigidbody2D::getPosition() {
	return this->position;
}

float Rigidbody2D::getRotation() {
	return this->rotation;
}

float Rigidbody2D::getMass() {
	return this->mass;
}

float Rigidbody2D::getInverseMass() {
	return this->inverseMass;
}

Collider2D* Rigidbody2D::getCollider() {
	return this->collider;
}

float Rigidbody2D::getCor() {
	return this->cor;
}

void Rigidbody2D::setMass(float mass) {
	this->mass = mass;
	if (floatGT(mass, 0.f)) {
		this->inverseMass = 1 / mass;
	}
}

void Rigidbody2D::setPosition(Vector2f position) {
	this->position = position;
}

void Rigidbody2D::setRotation(float rotation) {
	this->rotation = rotation;
}

void Rigidbody2D::setTransform(Vector2f position, float rotation) {
	this->position = position;
	this->rotation = rotation;
}

void Rigidbody2D::setTransform(Vector2f position) {
	this->position = position;
}

void Rigidbody2D::setCor(float cor) {
	this->cor = cor;
}

void Rigidbody2D::setLinearVelocity(Vector2f velocity) {
	this->linearVelocity = velocity;
}

bool Rigidbody2D::hasInfiniteMass() {
	return (floatCompare(this->mass, 0));
}

void Rigidbody2D::physicsUpdate(float dt) {
	//Can't work with zero mass objects (They represent immovable objects)
	if (floatCompare(this->mass, 0.0f)) return;

	//Calculate linear velocity and update position:
	Vector2f acceleration = forceAccumulator * inverseMass;
	this->linearVelocity += acceleration * dt;
	this->position += linearVelocity * dt;
	
	syncCollisionTransforms();
	clearAccumulators();
}

void Rigidbody2D::syncCollisionTransforms() {
	//TODO Sync object with render copy:
	//Will likely use SFML copy
}

void Rigidbody2D::clearAccumulators() {
	this->forceAccumulator = Vector2f();
}

void Rigidbody2D::addForce(Vector2f force) {
	this->forceAccumulator += force;
}

void Rigidbody2D::setCollider(Collider2D* collider) {
	this->collider = collider;
}