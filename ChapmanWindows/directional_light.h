#pragma once

#include "light.h"

class directional_light final : public light
{
public:
	directional_light(vector3 direction, color color, double intensity);

	auto direction() const->vector3;
	auto color() const->color;
	auto intensity() const -> double;

	auto contribution(
		const scene& scene,
		const vector3& hit_point,
		const vector3& surface_normal,
		const ::color& object_color,
		double light_reflected)
		->::color override;

private:
	vector3 _direction;
};

