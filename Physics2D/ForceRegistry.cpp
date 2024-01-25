#include "ForceRegistry.h"

using namespace Physics2D;
using std::vector;

ForceRegistry::ForceRegistry():
	registry()
{}

void ForceRegistry::add(ForceGenerator* fg, Rigidbody2D* rb) {
	registry.push_back(new ForceRegistration(fg, rb));
}

void ForceRegistry::add(ForceRegistration* fr) {
	registry.push_back(fr);
}

//Removes and frees all elements with a given Force Generator and Rigidbody
void ForceRegistry::remove(ForceRegistration* fr) {
	for (vector<ForceRegistration*>::iterator registration = registry.begin();
		registration < registry.end();
		registration++) {
		if (fr->equals<ForceRegistration*>(*registration)) {
			registry.erase(registration);
			delete* registration;
		}
	}
}

void ForceRegistry::clear() {
	registry.clear();
}

void ForceRegistry::updateForces(float dt) {
	for (vector<ForceRegistration*>::iterator r = registry.begin(); r < registry.end() ; r++) {
		(*r)->forceGenerator->updateForce(*(*r)->rigidbody, dt);
	}
}