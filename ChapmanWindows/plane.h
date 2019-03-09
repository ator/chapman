#pragma once

#include "point.h"
#include "vector3.h"
#include "color.h"
#include "intersectable.h"

class plane : public intersectable
{
public:
	plane(point center, vector3 normal, color color);

	auto intersects(const ray& ray) const -> boost::optional<intersection> override;

private:
	point _center;
	vector3 _normal;
	color _color;
};

