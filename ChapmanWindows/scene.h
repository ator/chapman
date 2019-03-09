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

	auto add_sphere(point center, double radius, color color) -> void;
	auto add_plane(point center, vector3 normal, color color) -> void;
	auto add_light(point center, double radius, color color) -> void;

	auto render(image& image) const -> void;

private:
	double _field_of_view_adjustment;
	std::vector<std::shared_ptr<intersectable>> _objects;
	std::vector<std::shared_ptr<light>> _lights;

	auto add_object(std::shared_ptr<intersectable> object) -> void;
	auto create_primary_ray(size_t x, size_t y, const image& image) const ->ray;
};

