#pragma once

#include "point.h"
#include "color.h"
#include "sphere.h"

class light : public sphere
{
public:
	light(point center, double radius, ::color color);
};
