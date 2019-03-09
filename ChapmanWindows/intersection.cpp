#include "intersection.h"

intersection::intersection(const double distance, const ::color color) :
	_distance(distance),
	_color(color)
{}

auto intersection::distance() const -> double
{
	return _distance;
}

auto intersection::color() const -> ::color
{
	return _color;
}
