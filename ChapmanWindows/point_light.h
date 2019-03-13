#pragma once

#include "color.h"
#include "light.h"

class point_light final : public light
{
public:
	point_light(vector3 center, ::color color, double intensity);

	auto direction_from(const vector3& hit_point) -> vector3 override;
	auto distance(const vector3& hit_point) -> double override;
	auto intensity(const vector3& hit_point) -> double override;

private:
	const vector3 _center;
};
