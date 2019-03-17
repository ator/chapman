#include <boost/math/constants/constants.hpp>

#include "sphere.h"
#include "intersection.h"

sphere::sphere(const vector3 center, const double radius, std::shared_ptr<::material> material) :
	intersectable(std::move(material)),
	_center(center),
	_radius(radius),
	_radius_squared(radius * radius)
{}

auto sphere::intersection_distance(const ray& ray) const -> boost::optional<double>
{
	const auto l = _center - ray.origin();
	const auto adj = l * ray.direction();
	const auto d2 = l * l - adj * adj;
	
	if (d2 > _radius_squared)
	{
		return {};
	}
	
	const auto thc = std::sqrt(_radius_squared - d2);
	const auto t0 = adj - thc;
	const auto t1 = adj + thc;
	
	if (t0 < 0.0 && t1 < 0.0)
	{
		return {};
	}
	
	const auto distance = t0 < t1 ? t0 : t1;
	return { distance };
}

auto sphere::surface_normal(const vector3& hit_point) const -> vector3
{
	return (hit_point - _center).normalize();
}
