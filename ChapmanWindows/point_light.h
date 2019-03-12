#pragma once

#include "color.h"
#include "sphere.h"
#include "light.h"

class point_light final : public light
{
public:
	point_light(vector3 center, double radius, color color, double intensity);

	auto color() const->color;
	auto intensity() const -> double;

	auto intersects(const ray& ray) const -> boost::optional<double>;

	auto contribution(
		const scene& scene,
		const vector3& hit_point,
		const vector3& surface_normal,
		const ::color& object_color,
		double light_reflected)
		->::color override;

private:
	const sphere _light_bulb;
};
