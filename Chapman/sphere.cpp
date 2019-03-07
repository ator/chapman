#include "sphere.h"

sphere::sphere(point center, double radius) :
	_center(center),
	_radius(radius)
{}

sphere::sphere(sphere&& s) noexcept
{
	_center = s._center;
	_radius = s._radius;
}

auto sphere::operator=(sphere&& s) noexcept-> sphere&
{
	_center = s._center;
	_radius = s._radius;
	return *this;
}

auto sphere::intersects(const ray& ray) const -> bool
{
	return false;
}
