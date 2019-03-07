#pragma once
#include <iostream>

#include "point.h"
#include "ray.h"

class sphere
{
public:
	sphere() = default;
	sphere(point center, double radius);
	sphere(sphere& s) = default;
	sphere(sphere&& s) noexcept;
	auto operator=(const sphere& s)->sphere& = default;
	auto operator=(sphere&& s) noexcept->sphere&;
	~sphere() = default;

	auto intersects(const ray& ray) const -> bool;

	friend auto operator<<(std::ostream& os, const sphere& s)->std::ostream&;

private:
	point _center{};
	double _radius{};
};

inline std::ostream& operator<<(std::ostream& os, const sphere& s)
{
	os << s._center << "->" << s._radius;
	return os;
}
