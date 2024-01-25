#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <Physics2D.h>
#include <cmath>
#include <iostream>

void fluidSim();
void testPhysicsWorld();
void visualizeCircleVSBox();
void visualizeCircleVSCircle();
void visualizeRaycastBox();
void runBackgroundTests();
bool testPointOnLine();
bool testPointInCircle();
bool testPointInAABB();
bool testPointInBox();
bool testRotateVector2f();
bool testLineVSCircle();
bool testLineVSAABB();
bool testLineVSBox();
bool testRaycastCircle();
bool testRaycastAABB();
bool testRaycastBox();