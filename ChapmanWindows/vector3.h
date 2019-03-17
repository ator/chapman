#pragma once
#include <iostream>

class vector3
{
public:
	static const vector3 ZERO;

	vector3() = default;
	vector3(double x, double y, double z);

	auto x() const -> double;
	auto y() const -> double;
	auto z() const -> double;

	auto operator==(const vector3& v) const -> bool;
	auto operator!=(const vector3& v) const -> bool;

	auto operator+(const vector3& v) const->vector3;
	auto operator-(const vector3& v) const->vector3;
	auto operator^(const vector3& v) const->vector3;
	auto operator*(const vector3& v) const -> double;
	
	auto operator*(double factor) const->vector3;

	auto operator-() const->vector3;

	auto length2() const -> double;
	auto length() const -> double;

	auto normalize() const ->vector3;

	friend std::ostream& operator<<(std::ostream& os, const vector3& v);

private:
	double _x{};
	double _y{};
	double _z{};
};
