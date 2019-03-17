#pragma once

#include "vector3.h"
#include "intersectable.h"

class plane : public intersectable
{
public:
	plane(vector3 origin, vector3 normal, std::shared_ptr<::material> material);

	auto intersection_distance(const ray& ray) const -> boost::optional<double> override;
	auto surface_normal(const vector3&) const -> vector3 override;

private:
	vector3 _origin;
	vector3 _normal;
};

