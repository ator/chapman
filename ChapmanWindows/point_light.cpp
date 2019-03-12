#include "point_light.h"
#include "intersection.h"

point_light::point_light(const vector3 center, const double radius, const ::color color, const double intensity) :
	light(color, intensity),
	_light_bulb(center, radius, color)
{}

auto point_light::color() const -> ::color
{
	return _light_bulb.color();
}

auto point_light::intensity() const -> double
{
	return _intensity;
}

auto point_light::intersects(const ray& ray) const -> boost::optional<double>
{
	return _light_bulb.intersection_distance(ray);
}

auto point_light::contribution(
	const scene& scene,
	const vector3& hit_point,
	const vector3& surface_normal,
	const ::color& object_color,
	const double light_reflected)
	-> ::color
{
	return color::black;
}
