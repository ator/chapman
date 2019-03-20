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

	auto get_color() const -> ::color;

	virtual auto direction_from(const vector3& hit_point)->vector3 = 0;
	virtual auto intensity(const vector3& hit_point)->double = 0;
	virtual auto distance(const vector3& hit_point)->double = 0;

protected:
	const ::color _color;
	const double _intensity;
};
