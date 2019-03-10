#include "directional_light.h"

directional_light::directional_light(const vector3 direction, const ::color color, const double intensity) :
	_direction(direction),
	_color(color),
	_intensity(intensity)
{}

auto directional_light::direction() const -> vector3
{
	return _direction;
}

auto directional_light::color() const -> ::color
{
	return _color;
}

auto directional_light::intensity() const -> double
{
	return _intensity;
}
