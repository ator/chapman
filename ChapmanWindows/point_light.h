#pragma once

#include "color.h"
#include "sphere.h"
#include "light.h"

class point_light final : public light
{
public:
	point_light(vector3 center, double radius, ::color color, double intensity);

	auto color() const->color;
	auto intensity() const -> double;

	auto intersects(const ray& ray) const -> boost::optional<double>;

private:
	sphere _light_bulb;
	double _intensity;
};
