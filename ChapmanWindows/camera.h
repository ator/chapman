#pragma once

#include "vector3.h"
#include "ray.h"
#include "image.h"

class camera
{
public:
	camera(vector3 position, vector3 look_at, vector3 up, double field_of_view_degrees);

	auto create_primary_ray(size_t x, size_t y, std::shared_ptr<image> image) const->ray;

private:
	const vector3 _position;
	double _field_of_view_adjustment;
	vector3 _u;
	vector3 _v;
	vector3 _w;
};

