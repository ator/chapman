#pragma once

#include "ray.h"
#include "intersectable.h"

class sphere : public intersectable
{
public:
	sphere(vector3 center, double radius, std::shared_ptr<::material> material);

	auto intersection_distance(const ray& ray) const -> boost::optional<double> override;
	auto surface_normal(const vector3& hit_point) const -> vector3 override;

private:
	vector3 _center;
	double _radius;
	double _radius_squared;
};
