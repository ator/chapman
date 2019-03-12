#pragma once
#include "image.h"
#include "intersectable.h"
#include "light.h"

class scene
{
public:
	explicit scene(double field_of_view_degrees);
	scene(const scene& s) = delete;
	scene(const scene&& s) = delete;
	auto operator=(const scene& s)->scene& = delete;
	auto operator=(scene&& s)->scene& = delete;
	~scene() = default;

	auto add_sphere(vector3 center, double radius, color color) -> void;
	auto add_plane(vector3 center, vector3 normal, color color) -> void;
	auto add_directional_light(vector3 direction, color color, double intensity) -> void;
	auto add_point_light(vector3 center, double radius, color color, double intensity) -> void;

	auto render(image& image) const -> void;
	auto trace(ray ray) const->boost::optional<intersection>;

private:
	const double _field_of_view_adjustment;
	std::vector<std::shared_ptr<intersectable>> _objects;
	std::vector<std::shared_ptr<light>> _lights;

	auto add_object(std::shared_ptr<intersectable> object) -> void;
	auto add_light(std::shared_ptr<light> light) -> void;
	auto create_primary_ray(size_t x, size_t y, const image& image) const->ray;
};

