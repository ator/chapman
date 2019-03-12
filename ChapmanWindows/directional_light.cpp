#include "directional_light.h"
#include "ray.h"
#include "scene.h"
#include "intersection.h"

directional_light::directional_light(const vector3 direction, const ::color color, const double intensity) :
	light(color, intensity),
	_direction(direction)
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

auto directional_light::contribution(
	const ::scene& scene,
	const vector3& hit_point,
	const vector3& surface_normal,
	const ::color& object_color,
	const double light_reflected)
	-> ::color
{
	const auto direction_to_light = -_direction;

	const auto shadow_bias = 1E-13;
	const auto shadow_ray = ray{ (hit_point + surface_normal * shadow_bias), direction_to_light };
	const auto in_shadow = scene.trace(shadow_ray);
	if (!in_shadow)
	{
		const auto light_power = surface_normal * direction_to_light * _intensity;
		const auto magnitude = light_power * light_reflected;
		return object_color * _color * magnitude;
	}
	return color::black;
}
