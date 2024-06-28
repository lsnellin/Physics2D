#include "ObjectList.h"

using sf::Vector2f;
using Physics2D::ObjectList;
using Physics2D::PhysicsObject;
using Physics2D::Collider2D;
using std::vector;

ObjectList::ObjectList() :
	objects({})
{
}

ObjectList::ObjectList(vector<PhysicsObject*> objects) :
	objects(objects)
{
}

void ObjectList::doUpdates() {
	for (PhysicsObject* object : objects) {
		object->updateFromRigidbody();
	}
}

vector<PhysicsObject*> ObjectList::getObjects() {
	return objects;
}
