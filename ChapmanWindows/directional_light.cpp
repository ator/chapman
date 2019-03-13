#include "directional_light.h"
#include "ray.h"
#include "scene.h"
#include "intersection.h"

directional_light::directional_light(const vector3 direction, const ::color color, const double intensity) :
	light(color, intensity),
	_direction(direction)
{}

auto directional_light::direction_from(const vector3&) -> vector3
{
	return -_direction;
}

auto directional_light::distance(const vector3&) -> double
{
	return std::numeric_limits<double>::max();
}

auto directional_light::intensity(const vector3&) -> double
{
	return _intensity;
}
