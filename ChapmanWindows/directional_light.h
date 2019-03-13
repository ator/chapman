#pragma once

#include "light.h"

class directional_light final : public light
{
public:
	directional_light(vector3 direction, ::color color, double intensity);

	auto direction_from(const vector3& hit_point) -> vector3 override;
	auto distance(const vector3& hit_point) -> double override;
	auto intensity(const vector3& hit_point) -> double override;

private:
	vector3 _direction;
};

