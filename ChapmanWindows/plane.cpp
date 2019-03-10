#include "plane.h"
#include "intersection.h"

plane::plane(const vector3 center, const vector3 normal, const ::color color, const double albedo) :
	intersectable(color, albedo),
	_center(center),
	_normal(normal)
{}

auto plane::intersects(const ray& ray) const -> boost::optional<double>
{
	const auto denominator = _normal * ray.direction();
	if (denominator > 1e-6)
	{
		const auto v = _center - ray.origin();
		const auto distance = v * _normal / denominator;
		if (distance >= 0.0)
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
