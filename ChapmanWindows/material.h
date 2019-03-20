#pragma once
#include "color.h"

class material
{
public:
	material(color color, double diffuse_reflection, double specular_reflection, double albedo, double reflectivity);

	auto surface_color() const->color;
	auto diffuse_reflection() const -> double;
	auto specular_reflection() const -> double;
	auto light_reflected() const -> double;
	auto reflectivity() const -> double;

private:
	const ::color _color;
	const double _diffuse_reflection;
	const double _specular_reflection;
	const double _light_reflected;
	const double _reflectivity;
};

