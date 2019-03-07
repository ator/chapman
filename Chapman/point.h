#pragma once
#include <iostream>

class point
{
public:
	static point zero;

	point() = default;
	point(double x, double y, double z);
	point(const point& v) = default;
	point(const point&& v) noexcept;
	auto operator=(const point& v)->point& = default;
	auto operator=(point&& v) noexcept->point&;	
	~point() = default;

	auto operator==(const point& v) const -> bool;
	auto operator!=(const point& v) const -> bool;

	auto operator+(const point& v) const->point;
	auto operator-(const point& v) const->point;

	auto operator-() const->point;

	friend auto operator<<(std::ostream& os, const point& p)->std::ostream&;

private:
	double _x{};
	double _y{};
	double _z{};
};

inline std::ostream& operator<<(std::ostream& os, const point& p)
{
	os << "(" << p._x << ", " << p._y << ", " << p._z << ")";
	return os;
}
