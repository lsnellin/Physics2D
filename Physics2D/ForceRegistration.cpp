#include "ForceRegistration.h"

using namespace Physics2D;

ForceRegistration::ForceRegistration(ForceGenerator *forceGenerator, Rigidbody2D *rigidbody):
	forceGenerator(forceGenerator),
	rigidbody(rigidbody)
{}