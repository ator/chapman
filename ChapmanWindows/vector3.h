#pragma once

class point;

class vector3
{
public:
	static vector3 zero;

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
	
	auto operator+(const point& p) const->vector3;

	auto operator*(double factor) const->vector3;

	auto operator-() const->vector3;

	auto length2() const -> double;
	auto length() const -> double;

	auto normalize()->vector3&;

private:
	double _x{};
	double _y{};
	double _z{};
};
