#include "sphere.h"

sphere::sphere(const point center, const double radius, const ::color color) :
	_center(center),
	_radius(radius),
	_radius_squared(radius * radius),
	_color(color)
{}

auto sphere::color() const -> ::color
{
	return _color;
}

auto sphere::intersects(const ray& ray) const -> boost::optional<intersection>
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
	return { {distance, _color} };
}
