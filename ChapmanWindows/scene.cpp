#include <iostream>
#include <thread>
#include <queue>

#include <boost/math/constants/constants.hpp>
#include <boost/thread.hpp>
#include <boost/thread/future.hpp>

#include "scene.h"
#include "sphere.h"
#include "plane.h"
#include "intersection.h"
#include "directional_light.h"
#include "point_light.h"

scene::scene(const color ambient_light_color, const double ambient_light_intensity, const size_t max_trace_depth) :
	_mersenne_twister_engine(_random_device()),
	_random_distribution(-1.0, 1.0),
	_ambient_light_color(ambient_light_color),
	_ambient_light_intensity(ambient_light_intensity),
	_max_trace_depth(max_trace_depth)
{}

auto scene::add_material(
	const color color,
	const double diffuse_reflection,
	const double specular_reflection,
	const double reflectivity,
	const double albedo)
	-> std::shared_ptr<material>
{
	auto material = std::make_shared<::material>(color, diffuse_reflection, specular_reflection, reflectivity, albedo);
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

auto scene::render(const std::shared_ptr<camera>& camera, const std::shared_ptr<image>& image) -> void
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

void scene::render(const std::shared_ptr<camera>& camera,
	const std::shared_ptr<image>& image,
	const size_t start_x, const size_t stop_x, 
	const size_t start_y, const size_t stop_y) 
{
	for (auto y = start_y; y < stop_y; ++y)
	{
		for (auto x = start_x; x < stop_x; ++x)
		{
			auto color = color::BLACK;

			for (auto sub_pixel = 0; sub_pixel < 4; ++sub_pixel)
			{
				const auto x_offset = _random_distribution(_mersenne_twister_engine);
				const auto y_offset = _random_distribution(_mersenne_twister_engine);

				const auto primary_ray = camera->create_primary_ray(x + x_offset, y + y_offset, image);
				
				color += trace(primary_ray, 1, 1);
			}

			image->set_pixel(x, y, color / 4);
		}
	}
}

auto scene::trace(ray ray, const size_t depth, const double total_reflectivity) const -> color
{
	const auto minimum_reflectivity = 0.001;
	if (total_reflectivity < minimum_reflectivity || depth > _max_trace_depth) return color::BLACK;

	auto intersection = find_intersection(ray);
	if (intersection)
	{
		const auto shadow_bias = 1E-6;
		const auto four_pi = 4 * boost::math::constants::pi<double>();

		const auto hit_point = ray.origin() + ray.direction() * intersection->distance();
		const auto surface_normal = intersection->object()->surface_normal(hit_point);

		const auto material = intersection->object()->get_material();
		const auto object_color = material->surface_color();
		//const auto light_reflected = material->light_reflected();

		const auto direction_to_ambient_light = ray.origin() - hit_point;
		const auto distance_to_hit_point = direction_to_ambient_light.length();
		ray.distance_traveled() += distance_to_hit_point;

		const auto ambient_light_power = std::fmax(0.0, surface_normal * direction_to_ambient_light) * _ambient_light_intensity;
		const auto object_distance_squared = distance_to_hit_point * distance_to_hit_point;
		const auto object_distance_factor = fmax(1, four_pi * object_distance_squared);
		auto const ambient_light_magnitude = ambient_light_power / object_distance_factor;
		auto color = object_color * _ambient_light_color * ambient_light_magnitude;

		for (auto& light : _lights)
		{
			const auto direction_to_light = light->direction_from(hit_point);

			const ::ray shadow_ray{ hit_point + surface_normal * shadow_bias, direction_to_light };

			const auto shadow_intersection = find_intersection(shadow_ray);
			const auto distance_to_light = light->distance(hit_point);
			const auto in_light = !shadow_intersection || shadow_intersection->distance() > distance_to_light;

			if (in_light)
			{
				const auto distance_to_light_squared = distance_to_light * distance_to_light;
				const auto light_distance_factor = std::fmax(1, four_pi * distance_to_light_squared);
				const auto light_intensity = light->intensity(hit_point);
				const auto light_color = light->get_color();

				const auto diffuse_light = diffuse_light_contribution(direction_to_light, surface_normal);
				const auto diffuse_reflection = material->diffuse_reflection();
				const auto diffuse_light_magnitude = diffuse_light * light_intensity * diffuse_reflection / light_distance_factor;

				const auto specular_light = specular_light_contribution(direction_to_light, surface_normal);
				const auto specular_reflection = material->specular_reflection();
				const auto specular_light_magnitude = specular_light * light_intensity * specular_reflection / light_distance_factor;

				const auto surface_color = object_color * light_color;

				color += surface_color * diffuse_light_magnitude;
				color += surface_color * specular_light_magnitude;
			}
		}

		const auto object_reflectivity = intersection->object()->get_material()->reflectivity();
		if (object_reflectivity > 0)
		{
			const auto reflection_direction = ray.direction() - surface_normal * 2 * (ray.direction() * surface_normal);
			::ray reflection_ray(hit_point + surface_normal * shadow_bias, reflection_direction);

			const auto reflection_distance_squared = reflection_ray.distance_traveled() * reflection_ray.distance_traveled();
			const auto reflection_distance_factor = std::fmax(1, four_pi * reflection_distance_squared);
			const auto reflection_magnitude = object_reflectivity / reflection_distance_factor;

			const auto reflection_color = trace(reflection_ray, depth + 1, total_reflectivity * reflection_magnitude);

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
	const auto specular_angle = std::fmax(0.0, surface_normal * direction_to_light);
	const auto specular_power = pow(specular_angle, 6);
	return specular_power;
}
