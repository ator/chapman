#include <boost/math/constants/constants.hpp>

#include "intersectable.h"

intersectable::intersectable(const ::color color, const double albedo) :
	_color(color),
	_light_reflected(albedo / boost::math::constants::pi<double>())
{}

auto intersectable::color() const -> ::color
{
	return _color;
}

auto intersectable::light_reflected() const -> double
{
	return _light_reflected;
}
