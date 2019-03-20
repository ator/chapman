#include "material.h"
#include <boost/math/constants/constants.hpp>

material::material(const ::color color, const double diffuse_reflection, const double specular_reflection, const double albedo, double reflectivity) :
	_color(color),
	_diffuse_reflection(diffuse_reflection),
	_specular_reflection(specular_reflection),
	_light_reflected(albedo / boost::math::constants::pi<double>()),
	_reflectivity(reflectivity)
{}

auto material::surface_color() const -> ::color
{
	return _color;
}

auto material::diffuse_reflection() const -> double
{
	return _diffuse_reflection;
}

auto material::specular_reflection() const -> double
{
	return _specular_reflection;
}

auto material::light_reflected() const -> double
{
	return _light_reflected;
}

auto material::reflectivity() const -> double
{
	return _reflectivity;
}
