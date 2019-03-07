#pragma once
#include <iostream>

class vector3
{
public:
	static vector3 zero;

	vector3() = default;
	vector3(double x, double y, double z);
	vector3(const vector3& v) = default;
	vector3(const vector3&& v) noexcept;
	auto operator=(const vector3& v)->vector3& = default;
	auto operator=(vector3&& v) noexcept->vector3&;
	~vector3() = default;

	auto operator==(const vector3& v) const -> bool;
	auto operator!=(const vector3& v) const -> bool;

	auto operator+(const vector3& v) const->vector3;
	auto operator-(const vector3& v) const->vector3;
	auto operator^(const vector3& v) const->vector3;
	auto operator*(const vector3& v) const -> double;

	auto operator-() const->vector3;

	auto length2() const -> double;
	auto length() const -> double;

	auto normalize()->vector3&;

	friend auto operator<<(std::ostream& os, const vector3& v)->std::ostream&;

private:
	double _x{};
	double _y{};
	double _z{};
};

inline std::ostream& operator<<(std::ostream& os, const vector3& v)
{
	os << "[" << v._x << ", " << v._y << ", " << v._z << "]";
	return os;
}
