#pragma once

#include <boost/optional.hpp>

#include "color.h"
#include "ray.h"

class intersection;

class intersectable
{
public:
	intersectable(::color color, double albedo);
	intersectable(const intersectable& other) = delete;
	intersectable(intersectable&& other) = delete;
	auto operator=(const intersectable& other)->intersectable& = delete;
	auto operator=(intersectable&& other)->intersectable& = delete;
	virtual ~intersectable() = default;

	auto color() const -> ::color;
	auto light_reflected() const -> double;

	virtual auto intersection_distance(const ray& ray) const -> boost::optional<double> = 0;
	virtual auto surface_normal(const vector3& hit_point) const->vector3 = 0;

private:
	::color _color;
	double _light_reflected;
};
