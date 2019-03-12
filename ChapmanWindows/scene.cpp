#include <iostream>

#include <boost/math/constants/constants.hpp>

#include "scene.h"
#include "sphere.h"
#include "plane.h"
#include "intersection.h"
#include "directional_light.h"
#include "point_light.h"

scene::scene(const double field_of_view_degrees) :
	_field_of_view_adjustment(std::tan(field_of_view_degrees * boost::math::constants::pi<double>() / 180 / 2))
{}

auto scene::add_sphere(const vector3 center, const double radius, const ::color color) -> void
{
	add_object(std::make_shared<::sphere>(center, radius, color));
}

auto scene::add_plane(const vector3 center, const vector3 normal, const color color) -> void
{
	add_object(std::make_shared<plane>(center, normal.normalize(), color));
}

auto scene::add_directional_light(const vector3 direction, const color color, const double intensity) -> void
{
	add_light(std::make_shared<directional_light>(direction.normalize(), color, intensity));
}

auto scene::add_point_light(const vector3 center, const double radius, const color color, const double intensity) -> void
{
	add_light(std::make_shared<point_light>(center, radius, color, intensity));
}

auto scene::render(image& image) const -> void
{
	for (size_t y = 0; y < image.height(); ++y)
	{
		for (size_t x = 0; x < image.width(); ++x)
		{
			auto primary_ray = create_primary_ray(x, y, image);
			auto color = ::color::black;

			auto intersection = trace(primary_ray);
			if (intersection)
			{
				const auto hit_point = primary_ray.origin() + primary_ray.direction() * intersection->distance();
				const auto surface_normal = intersection->object()->surface_normal(hit_point);

				for (auto& light : _lights)
				{
					const auto object_color = intersection->object()->color();
					const auto light_reflected = intersection->object()->light_reflected();
					color += light->contribution(*this, hit_point, surface_normal, object_color, light_reflected);
				}
			}

			image.set_pixel(x, y, color.clamp());
		}
	}
}

auto scene::add_object(std::shared_ptr<intersectable> object) -> void
{
	_objects.emplace_back(std::move(object));
}

auto scene::add_light(std::shared_ptr<light> light) -> void
{
	_lights.emplace_back(std::move(light));
}

auto scene::create_primary_ray(const size_t x, const size_t y, const image& image) const -> ray
{
	const auto pixel_center_x = static_cast<double>(x) + 0.5;
	const auto pixel_center_y = static_cast<double>(y) + 0.5;

	const auto sensor_x = pixel_center_x / image.width() * 2.0 - 1.0;
	const auto sensor_y = 1.0 - pixel_center_y / image.height() * 2.0;

	//std::cout << sensor_x << ", " << sensor_y << std::endl;

	vector3 direction(sensor_x * image.aspect_ratio() * _field_of_view_adjustment, sensor_y * _field_of_view_adjustment, -1.0);
	return { vector3::zero , direction.normalize() };
}

auto scene::trace(const ray ray) const -> boost::optional<intersection>
{
	boost::optional<intersection> nearest_object;

	for (auto& object : _objects)
	{
		auto intersection = object->intersection_distance(ray);
		if (intersection)
		{
			const auto distance = *intersection;
			if (!nearest_object || distance < nearest_object->distance())
			{
				nearest_object = { { distance, object } };
			}
		}
	}

	return nearest_object;
}
