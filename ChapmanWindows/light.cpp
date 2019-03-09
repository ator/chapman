#include "light.h"

light::light(const point center, const double radius, const ::color color) :
	sphere(center, radius, color)
{}
