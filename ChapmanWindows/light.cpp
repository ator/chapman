#include "light.h"

light::light(const ::color color, const double intensity) :
	_color(color),
	_intensity(intensity)
{}

auto light::get_color() const -> ::color
{
	return _color;
}
