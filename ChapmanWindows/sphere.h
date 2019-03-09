#pragma once

#include "point.h"
#include "ray.h"
#include "color.h"
#include "intersectable.h"

class sphere : public intersectable
{
public:
	sphere(point center, double radius, color color);

	auto color() const->color;

	auto intersects(const ray& ray) const -> boost::optional<intersection> override;

private:
	point _center;
	double _radius;
	double _radius_squared;
	::color _color;
};
