#include "camera.h"
#include <boost/math/constants/constants.hpp>
#include "ray.h"
#include "image.h"

camera::camera(vector3 position, vector3 look_at, vector3 up, double field_of_view_degrees) :
	_position(position)
{
	_field_of_view_adjustment = std::tan(field_of_view_degrees * boost::math::constants::pi<double>() / 180 / 2);
	_w = (look_at - position).normalize();
	_u = (_w ^ up).normalize();
	_v = _u ^ _w;
	//std::cout << "u: " << _u << std::endl;
	//std::cout << "v: " << _v << std::endl;
	//std::cout << "w: " << _w << std::endl;
}

auto camera::create_primary_ray(const size_t x, const size_t y, const std::shared_ptr<image> image) const -> ray
{
	const auto pixel_center_x = static_cast<double>(x) + 0.5;
	const auto pixel_center_y = static_cast<double>(y) + 0.5;

	const auto sensor_x = pixel_center_x / image->width() * 2.0 - 1.0;
	const auto sensor_y = 1.0 - pixel_center_y / image->height() * 2.0;

	const auto alpha = _field_of_view_adjustment * sensor_x * image->aspect_ratio();
	const auto beta = _field_of_view_adjustment * sensor_y;

	const auto direction = (_u * alpha + _v * beta + _w).normalize();
	return { _position, direction };
}

