#include "point_light.h"
#include "intersection.h"

point_light::point_light(const vector3 center, const double radius, const ::color color, double intensity) :
	_light_bulb(center, radius, color),
	_intensity(intensity)
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
	return _light_bulb.intersects(ray);
}
