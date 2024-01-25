#include "RaycastResult.h"

using namespace Physics2D;
using sf::Vector2f;

RaycastResult::RaycastResult() :
	point(), normal(), t(), hit()
{
}

void RaycastResult::init(sf::Vector2f point, sf::Vector2f normal, float t, bool hit) {
	this->point.x = point.x;
	this->point.y = point.y;

	this->normal.x = normal.x;
	this->normal.y = normal.y;

	this->t = t;
	this->hit = hit;
}

void RaycastResult::reset(RaycastResult& result) {
	result.point = Vector2f(0.f, 0.f);
	result.normal = Vector2f(0.f, 0.f);
	result.t = -1;
	result.hit = false;
}

Vector2f RaycastResult::getNormal() {
	return this->normal;
}

Vector2f RaycastResult::getPoint() {
	return this->point;
}

float RaycastResult::getT() {
	return this->t;
}