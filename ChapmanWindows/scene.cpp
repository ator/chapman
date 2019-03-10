#include <boost/math/constants/constants.hpp>

#include "scene.h"
#include "sphere.h"
#include "plane.h"
#include "intersection.h"

scene::scene(const double field_of_view_degrees) :
	_field_of_view_adjustment(std::tan(field_of_view_degrees * 180 / boost::math::constants::pi<double>()))
{}

auto scene::add_sphere(const vector3 center, const double radius, const ::color color) -> void
{
	add_object(std::make_shared<::sphere>(center, radius, color));
}

auto scene::add_plane(const vector3 center, const vector3 normal, const color color) -> void
{
	add_object(std::make_shared<plane>(center, normal, color));
}

auto scene::add_directional_light(const vector3 direction, const color color, const double intensity) -> void
{
	_directional_lights.emplace_back(std::make_shared<directional_light>(direction, color, intensity));
}

auto scene::add_point_light(const vector3 center, const double radius, const color color, const double intensity) -> void
{
	_point_lights.emplace_back(std::make_shared<point_light>(center, radius, color, intensity));
}

auto scene::render(image& image) const -> void
{
	for (size_t y = 0; y < image.height(); ++y)
	{
		for (size_t x = 0; x < image.width(); ++x)
		{
			auto primary_ray = create_primary_ray(x, y, image);
			auto color = ::color::black;

			boost::optional<intersection> nearest_object;
			for (auto& object : _objects)
			{
				auto distance = object->intersects(primary_ray);
				if (distance)
				{
					if (!nearest_object || *distance < nearest_object->distance())
					{
						nearest_object = { { *distance, object } };
					}
				}
			}

			if (nearest_object)
			{
				const auto hit_point = primary_ray.origin() + primary_ray.direction() * nearest_object->distance();
				const auto surface_normal = nearest_object->object()->surface_normal(hit_point);

				for (auto& light : _directional_lights)
				{
					const auto direction_to_light = -light->direction();
					const auto light_power = surface_normal * direction_to_light * light->intensity();
					const auto adjustment = 1;// 1 / nearest_object->distance();
					const auto magnitude = light_power * nearest_object->object()->light_reflected() * adjustment;
					color += nearest_object->object()->color() * light->color() * magnitude;
				}
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
	return { vector3::zero, direction.normalize() };
}
