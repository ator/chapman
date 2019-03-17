#include <iostream>

#include <boost/math/constants/constants.hpp>
#include <boost/thread.hpp>
#include <boost/thread/future.hpp>

#include "scene.h"
#include "sphere.h"
#include "plane.h"
#include "intersection.h"
#include "directional_light.h"
#include "point_light.h"
#include <thread>
#include <queue>

scene::scene(const color ambient_light_color, const double ambient_light_intensity, const size_t max_trace_depth) :
	_ambient_light_color(ambient_light_color),
	_ambient_light_intensity(ambient_light_intensity),
	_max_trace_depth(max_trace_depth)
{}

auto scene::add_material(
	const color color,
	const double diffuse_reflection,
	const double specular_reflection,
	const double albedo,
	const double reflectivity)
	-> std::shared_ptr<material>
{
	auto material = std::make_shared<::material>(color, diffuse_reflection, specular_reflection, albedo, reflectivity);
	_materials.emplace_back(material);
	return material;
}

auto scene::add_sphere(const vector3 center, const double radius, std::shared_ptr<material> material) -> void
{
	add_object(std::make_shared<::sphere>(center, radius, material));
}

auto scene::add_plane(const vector3 center, const vector3 normal, std::shared_ptr<material> material) -> void
{
	add_object(std::make_shared<plane>(center, normal.normalize(), material));
}

auto scene::add_directional_light(const vector3 direction, const color color, const double intensity) -> void
{
	add_light(std::make_shared<directional_light>(direction.normalize(), color, intensity));
}

auto scene::add_point_light(const vector3 center, const color color, const double intensity) -> void
{
	add_light(std::make_shared<point_light>(center, color, intensity));
}

auto scene::render(const std::shared_ptr<camera>& camera, const std::shared_ptr<image>& image) const -> void
{
	auto number_of_threads = std::thread::hardware_concurrency();
	if (number_of_threads == 0)
	{
		number_of_threads = 1;
	}
	std::vector<std::shared_ptr<boost::thread>> threads;
	threads.reserve(number_of_threads);

	const auto thread_width = image->width() / (number_of_threads / 2);
	const auto thread_height = image->height() / (number_of_threads / 2);
	std::cout << "Running " << number_of_threads << " threads rendering " << thread_width << "x" << thread_height << " pixels each" << std::endl;

	boost::thread_group render_threads;
	for (size_t y = 0; y < image->height(); y = y + thread_height)
	{
		for (size_t x = 0; x < image->width(); x = x + thread_width)
		{
			const auto start_x = x;
			const auto start_y = y;
			const auto stop_x = start_x + thread_width < image->width() ? start_x + thread_width : image->width();
			const auto stop_y = start_y + thread_height < image->height() ? start_y + thread_height : image->height();
			render_threads.create_thread([=]() {
				try
				{
					render(camera, image, start_x, stop_x, start_y, stop_y);
				}
				catch (...)
				{
					std::cout << boost::current_exception_diagnostic_information();
				}
			});
		}
	}
	std::cout << "Waiting for render threads..." << std::endl;
	render_threads.join_all();
}

void scene::render(const std::shared_ptr<camera>& camera, const std::shared_ptr<image>& image, const size_t start_x, const size_t stop_x, const size_t start_y, const size_t stop_y) const
{
	for (auto y = start_y; y < stop_y; ++y)
	{
		for (auto x = start_x; x < stop_x; ++x)
		{
			const auto primary_ray = camera->create_primary_ray(x, y, image);

			const auto color = trace(primary_ray, 1);

			image->set_pixel(x, y, color);
		}
	}
}

auto scene::trace(ray ray, const size_t depth) const -> color
{
	if (depth > _max_trace_depth) return color::BLACK;

	auto intersection = find_intersection(ray);
	if (intersection)
	{
		const auto hit_point = ray.origin() + ray.direction() * intersection->distance();
		const auto surface_normal = intersection->object()->surface_normal(hit_point);

		const auto material = intersection->object()->material();
		const auto object_color = material->color();
		const auto light_reflected = material->light_reflected();

		const auto direction_to_ambient_light = ray.origin() - hit_point;
		const auto distance_to_hit_point = direction_to_ambient_light.length();
		ray.distance_traveled() += distance_to_hit_point;

		auto const ambient_light_power = std::fmax(0.0, surface_normal * direction_to_ambient_light * _ambient_light_intensity);
		auto const ambient_light_magnitude = ambient_light_power * light_reflected / distance_to_hit_point;
		auto color = object_color * _ambient_light_color * ambient_light_magnitude;

		for (auto& light : _lights)
		{
			const auto direction_to_light = light->direction_from(hit_point);

			const auto shadow_bias = 1E-6;
			const ::ray shadow_ray{ hit_point + surface_normal * shadow_bias, direction_to_light };

			const auto shadow_intersection = find_intersection(shadow_ray);
			const auto in_light = !shadow_intersection || shadow_intersection->distance() > light->distance(hit_point);

			if (in_light)
			{
				const auto light_intensity = light->intensity(hit_point);
				const auto light_color = light->color();

				const auto diffuse_light = diffuse_light_contribution(direction_to_light, surface_normal);
				const auto diffuse_reflection = light_reflected * material->diffuse_reflection();
				const auto diffuse_light_magnitude = diffuse_light * light_intensity * diffuse_reflection;

				const auto specular_light = specular_light_contribution(direction_to_light, surface_normal);
				const auto specular_reflection = material->specular_reflection();
				const auto specular_light_magnitude = specular_light * light_reflected * light_intensity * specular_reflection;

				const auto surface_color = object_color * light_color;

				color += surface_color * diffuse_light_magnitude;
				color += surface_color * specular_light_magnitude;
			}
		}

		const auto object_reflectivity = light_reflected * intersection->object()->material()->reflectivity();
		if (object_reflectivity > 0)
		{
			const auto reflection_direction = ray.direction() - surface_normal * 2 * (ray.direction() * surface_normal);
			::ray reflection_ray(hit_point, reflection_direction);

			auto reflection_color = trace(reflection_ray, depth + 1);

			auto reflection_magnitude = object_reflectivity / std::fmax(1, reflection_ray.distance_traveled());
			color += reflection_color * reflection_magnitude;
		}

		return color;
	}

	return color::BLACK;
}

auto scene::add_object(std::shared_ptr<intersectable> object) -> void
{
	_objects.emplace_back(std::move(object));
}

auto scene::add_light(std::shared_ptr<light> light) -> void
{
	_lights.emplace_back(std::move(light));
}

auto scene::find_intersection(const ray ray) const -> boost::optional<intersection>
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
auto scene::diffuse_light_contribution(const vector3 direction_to_light, const vector3 surface_normal) const -> double
{
	auto const light_power = std::fmax(0.0, surface_normal * direction_to_light);

	return light_power;
}

auto scene::specular_light_contribution(const vector3 direction_to_light, const vector3 surface_normal) const -> double
{
	const auto specular_angle = std::fmax(direction_to_light * surface_normal, 0);
	const auto specular_power = pow(specular_angle, 15);

	return specular_power;
}
