#include "point.h"

point point::zero(0,0,0);

point::point(const double x, const double y, const double z) :
	_x(x), _y(y), _z(z)
{}

point::point(const point&& v) noexcept
{
	_x = v._x;
	_y = v._y;
	_z = v._z;
}

auto point::operator=(point&& v) noexcept -> point&
{
	_x = v._x;
	_y = v._y;
	_z = v._z;
	return *this;
}

auto point::operator==(const point& v) const -> bool
{
	return _x == v._x && _y == v._y && _z == v._z;
}

auto point::operator!=(const point& v) const -> bool
{
	return !operator==(v);
}

auto point::operator+(const point& v) const -> vector3
{
	const auto x = _x + v._x;
	const auto y = _y + v._y;
	const auto z = _z + v._z;
	return { x, y, z };
}

auto point::operator-(const point& v) const -> vector3
{
	const auto x = _x - v._x;
	const auto y = _y - v._y;
	const auto z = _z - v._z;
	return { x, y, z };
}

auto point::operator-() const -> point
{
	return { -_x, -_y, -_z };
}
