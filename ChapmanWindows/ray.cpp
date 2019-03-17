#include "ray.h"

ray::ray(const vector3 origin, const vector3 direction) :
	_origin(origin),
	_direction(direction),
	_distance_traveled(0)
{}

ray::ray(const ray&& r) noexcept
{
	_origin = r._origin;
	_direction = r._direction;
}

auto ray::operator=(ray&& r) noexcept -> ray&
{
	_origin = r._origin;
	_direction = r._direction;
	return *this;
}

auto ray::origin() const -> const vector3&
{
	return _origin;
}

auto ray::direction() const -> const vector3&
{
	return _direction;
}

auto ray::distance_traveled() -> double&
{
	return _distance_traveled;
}
