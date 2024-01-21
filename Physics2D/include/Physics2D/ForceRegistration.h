#pragma once

#include "ForceGenerator.h"

namespace Physics2D {
	class ForceRegistration {
	private:
		Physics2D::ForceGenerator* forceGenerator;
		Physics2D::Rigidbody2D* rigidbody;
	public:
		friend class ForceRegistry;
		ForceRegistration(ForceGenerator* forceGenerator, Rigidbody2D* rigidbody);

		template <class T> 
		bool equals(T other);
	};

	template <class T>
	bool ForceRegistration::equals(T other) {
		if (!std::is_same<T, ForceRegistration>::value) return false;

		ForceRegistration otherFR = (ForceRegistration)other;
		return this->forceGenerator == otherFR.forceGenerator && this->rigidbody == otherFR.rigidbody;
	}
}