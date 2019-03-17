#include <cmath>
#include <iostream>

#include "vector3.h"
#include <iomanip>

const vector3 vector3::ZERO(0, 0, 0);

vector3::vector3(const double x, const double y, const double z) :
	_x(x), _y(y), _z(z)
{}

auto vector3::x() const -> double
{
	return _x;
}

auto vector3::y() const -> double
{
	return _y;
}

auto vector3::z() const -> double
{
	return _z;
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

auto vector3::operator*(const double factor) const -> vector3
{
	return { _x * factor, _y * factor, _z * factor };
}

auto vector3::operator-() const -> vector3
{
	return { -_x, -_y, -_z };
}

auto vector3::length2() const -> double
{
	return _x * _x + _y * _y + _z * _z;
}

auto vector3::length() const -> double
{
	return std::sqrt(length2());
}

auto vector3::normalize() const -> vector3
{
	const auto len = length();
	const auto x = _x / len;
	const auto y = _y / len;
	const auto z = _z / len;
	return {x, y, z};
}

std::ostream& operator<<(std::ostream& os, const vector3& v)
{
	os << std::setprecision(2) << "(" << v.x() << ", " << v.y() << ", " << v.z() << ")";
	return os;
}
