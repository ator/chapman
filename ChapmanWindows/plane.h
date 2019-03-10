#pragma once

#include "vector3.h"
#include "color.h"
#include "intersectable.h"

class plane : public intersectable
{
public:
	plane(vector3 center, vector3 normal, ::color color, double albedo = 1.0);

	auto intersects(const ray& ray) const -> boost::optional<double> override;
	auto surface_normal(const vector3&) const -> vector3 override;

private:
	vector3 _center;
	vector3 _normal;
};

