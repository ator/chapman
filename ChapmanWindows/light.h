#pragma once
#include "vector3.h"
#include "color.h"

class scene;

class light
{
public:
	light(color color, double intensity);
	light(const light& other) = delete;
	light(light&& other) = delete;
	auto operator=(const light& other)->light& = delete;
	auto operator=(light&& other)->light& = delete;
	virtual ~light() = default;

	virtual auto contribution(
		const scene& scene,
		const vector3& hit_point,
		const vector3& surface_normal,
		const color& object_color,
		double light_reflected)
		->color = 0;

protected:
	const color _color;
	const double _intensity;
};
