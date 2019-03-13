#include <boost/math/constants/constants.hpp>

#include "point_light.h"

point_light::point_light(const vector3 center, const ::color color, const double intensity) :
	light(color, intensity),
	_center(center)
{}

auto point_light::direction_from(const vector3& hit_point) -> vector3
{
	return (_center - hit_point).normalize();
}

auto point_light::distance(const vector3& hit_point) -> double
{
	return (_center - hit_point).length();
}

auto point_light::intensity(const vector3& hit_point) -> double
{
	const auto distance_to_light_2 = direction_from(hit_point).length2();
	return _intensity / (4.0 * boost::math::constants::pi<double>() * distance_to_light_2);
}
