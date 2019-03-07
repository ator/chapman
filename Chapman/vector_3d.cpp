#include "vector3.h"

vector3::vector3() : _x(0), _y(0), _z(0)
{}

vector3::vector3(double x, double y, double z) : _x(x), _y(y), _z(z)
{}

vector3::vector3(vector3&& v) noexcept
{
	_x = v._x;
	_y = v._y;
	_z = v._z;
}

auto vector3::operator=(vector3&& v) noexcept -> vector3&
{
	_x = v._x;
	_y = v._y;
	_z = v._z;
	return *this;
}

auto vector3::operator==(const vector3& v) const -> bool
{
	return _x == v._x && _y == v._y && _z == v._z;
}

auto vector3::operator!=(const vector3& v) const -> bool
{
	return !operator==(v);
}

auto vector3::operator+(const vector3& v) const -> vector3
{
	const auto x = _x + v._x;
	const auto y = _y + v._y;
	const auto z = _z + v._z;
	return { x, y, z };
}

auto vector3::operator-(const vector3& v) const -> vector3
{
	const auto x = _x - v._x;
	const auto y = _y - v._y;
	const auto z = _z - v._z;
	return { x, y, z };
}

auto vector3::operator^(const vector3& v) const -> vector3
{
	const auto x = _y * v._z - _z * v._y;
	const auto y = _z * v._x - _x * v._z;
	const auto z = _x * v._y - _y * v._x;
	return { x, y, z };
}

auto vector3::operator*(const vector3& v) const -> double
{
	return _x * v._x + _y * v._y + _z * v._z;
}

auto vector3::operator-() const -> vector3
{
	return { -_x, -_y, -_z };
}
