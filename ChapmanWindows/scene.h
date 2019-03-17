#pragma once
#include "image.h"
#include "intersectable.h"
#include "light.h"
#include "material.h"
#include "camera.h"

class scene
{
public:
	scene(color ambient_light_color, double ambient_light_intensity, size_t max_trace_depth);
	scene(const scene& s) = delete;
	scene(const scene&& s) = delete;
	auto operator=(const scene& s)->scene& = delete;
	auto operator=(scene&& s)->scene& = delete;
	~scene() = default;

	auto add_material(color color, double diffuse_reflection, double specular_reflection, double albedo, double reflectivity)
		->std::shared_ptr<material>;
	auto add_sphere(vector3 center, double radius, std::shared_ptr<material> material) -> void;
	auto add_plane(vector3 center, vector3 normal, std::shared_ptr<material> material) -> void;
	auto add_directional_light(vector3 direction, color color, double intensity) -> void;
	auto add_point_light(vector3 center, color color, double intensity) -> void;

	auto render(const std::shared_ptr<camera>& camera, const std::shared_ptr<image>& image) const -> void;

private:
	const color _ambient_light_color;
	const double _ambient_light_intensity;
	const size_t _max_trace_depth;
	std::vector<std::shared_ptr<intersectable>> _objects;
	std::vector<std::shared_ptr<light>> _lights;
	std::vector<std::shared_ptr<material>> _materials;

	auto render(const std::shared_ptr<camera>& camera, const std::shared_ptr<image>& image, size_t start_x, size_t stop_x, size_t start_y, size_t stop_y) const -> void;
	auto trace(ray ray, size_t depth) const->color;
	auto add_object(std::shared_ptr<intersectable> object) -> void;
	auto add_light(std::shared_ptr<light> light) -> void;
	auto find_intersection(ray ray) const->boost::optional<intersection>;
	auto diffuse_light_contribution(vector3 direction_to_light, vector3 surface_normal) const->double;
	auto specular_light_contribution(vector3 direction_to_light, vector3 surface_normal) const->double;
};

