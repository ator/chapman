#include "plane.h"
#include "intersection.h"

plane::plane(const vector3 origin, const vector3 normal, const ::color color, const double albedo) :
	intersectable(color, albedo),
	_origin(origin),
	_normal(normal)
{}

auto plane::intersection_distance(const ray& ray) const -> boost::optional<double>
{
	const auto denominator = _normal * ray.direction();
	if (std::fabs(denominator) > 1E-6)
	{
		const auto v = _origin - ray.origin();
		const auto distance = v * _normal / denominator;
		if (distance >= 1E-6)
		{
			return { distance };
		}
	}

	return {};
}

auto plane::surface_normal(const vector3&) const -> vector3
{
	return _normal;
}
