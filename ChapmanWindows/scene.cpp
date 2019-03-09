#include <boost/math/constants/constants.hpp>

#include "scene.h"
#include "sphere.h"
#include "plane.h"

scene::scene(const double field_of_view_degrees) :
	_field_of_view_adjustment(std::tan(field_of_view_degrees * 180 / boost::math::constants::pi<double>()))
{}

auto scene::add_sphere(point center, double radius, ::color color) -> void
{
	add_object(std::make_shared<::sphere>(center, radius, color));
}

auto scene::add_plane(point center, vector3 normal, color color) -> void
{
	add_object(std::make_shared<plane>(center, normal, color));
}

auto scene::add_light(point center, double radius, color color) -> void
{
	_lights.emplace_back(std::make_shared<light>(center, radius, color));
}

auto scene::render(image& image) const -> void
{
	for (size_t y = 0; y < image.height(); ++y)
	{
		for (size_t x = 0; x < image.width(); ++x)
		{
			auto primary_ray = create_primary_ray(x, y, image);
			auto color = ::color::black;
			std::vector<intersection> intersections;
			for (auto& object : _objects)
			{
				auto intersection = object->intersects(primary_ray);
				if (intersection)
				{
					intersections.emplace_back(*intersection);
				}
			}
			if (!intersections.empty())
			{
				std::sort(intersections.begin(), intersections.end(), [&](intersection a, intersection b)
				{
					return a.distance() < b.distance();
				});
				auto nearest = *intersections.begin();
				color = nearest.color() * (1 / nearest.distance());
			}
			image.set_pixel(x, y, color);
		}
	}
}

auto scene::add_object(std::shared_ptr<intersectable> object) -> void
{
	_objects.emplace_back(std::move(object));
}

auto scene::create_primary_ray(const size_t x, const size_t y, const image& image) const -> ray
{
	const auto pixel_center_x = static_cast<double>(x) + 0.5;
	const auto pixel_center_y = static_cast<double>(y) + 0.5;

	const auto sensor_x = (pixel_center_x / image.width() * 2.0 - 1.0) * image.aspect_ratio() * _field_of_view_adjustment;
	const auto sensor_y = (1.0 - pixel_center_y / image.height() * 2.0) * _field_of_view_adjustment;

	vector3 direction(sensor_x, sensor_y, -1.0);
	return { point::zero, direction.normalize() };
}
