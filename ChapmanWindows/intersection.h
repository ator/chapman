#pragma once

#include "color.h"

class intersection
{
public:
	intersection(double distance, ::color color);

	auto distance() const -> double;
	auto color() const->color;

private:
	double _distance;
	::color _color;
};

