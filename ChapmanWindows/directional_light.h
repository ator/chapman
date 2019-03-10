#pragma once

#include "light.h"
#include "vector3.h"
#include "color.h"

class directional_light final : public light
{
public:
	directional_light(vector3 direction, color color, double intensity);

	auto direction() const->vector3;
	auto color() const->color;
	auto intensity() const -> double;

private:
	vector3 _direction;
	::color _color;
	double _intensity;
};

