#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <Physics2D.h>
#include <cmath>
#include <iostream>

void visualizeAABB();
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