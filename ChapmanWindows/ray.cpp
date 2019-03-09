#include "ray.h"
#include <utility>

ray::ray(point origin, vector3 direction) :
	_origin(std::move(origin)),
	_direction(std::move(direction))
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

auto ray::origin() const -> const point&
{
	return _origin;
}

auto ray::direction() const -> const vector3&
{
	return _direction;
}
