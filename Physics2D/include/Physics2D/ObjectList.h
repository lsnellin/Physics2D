#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include "PhysicsObject.h"

namespace Physics2D {
	class ObjectList {
	private:
		std::vector<Physics2D::PhysicsObject*> objects;

	public:
		ObjectList();
		ObjectList(std::vector<Physics2D::PhysicsObject*> objects);
		std::vector<Physics2D::PhysicsObject*> getObjects();
		void doUpdates();
	};
}