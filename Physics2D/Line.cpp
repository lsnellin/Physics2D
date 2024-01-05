#include "Line.h"

using sf::Vector2f;
using namespace Physics2D;

Line::Line() :
start(Vector2f(0.f,0.f)),
end(Vector2f(0.f,0.f))
{
}

Line::Line(Vector2f start, Vector2f end) :
	start(start),
	end(end)
{
}

Vector2f Line::getStart() {
	return this->start;
}

Vector2f Line::getEnd() {
	return this->end;
}

Vector2f Line::getVector() {
	return this->end - this->start;
}