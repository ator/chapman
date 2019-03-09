#pragma once
#include <iostream>

#include "point.h"
#include "ray.h"
#include "intersectable.h"

class sphere : public intersectable
{
public:
	sphere(point center, double radius);

	auto intersects(const ray& ray) const -> bool override;

	friend auto operator<<(std::ostream& os, const sphere& s)->std::ostream&;

private:
	point _center;
	double _radius;
	double _radius_squared;
};

inline std::ostream& operator<<(std::ostream& os, const sphere& s)
{
	os << s._center << "->" << s._radius;
	return os;
}
