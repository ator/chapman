#include "sphere.h"

sphere::sphere(const point center, const double radius) : 
	_center(center),
	_radius(radius),
	_radius_squared(radius * radius)
{}

auto sphere::intersects(const ray& ray) const -> bool
{
	const auto hypotenuse = _center - ray.origin();
	const auto adjacent_length_squared = hypotenuse * ray.direction();
	const auto opposite_length_squared = hypotenuse * hypotenuse - adjacent_length_squared * adjacent_length_squared;
	return opposite_length_squared < _radius_squared;
}
