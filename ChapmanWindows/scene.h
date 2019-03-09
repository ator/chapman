#pragma once
#include "image.h"
#include "intersectable.h"

class scene
{
public:
	scene() = default;
	scene(const scene& s) = delete;
	scene(const scene&& s) = delete;
	auto operator=(const scene& s)->scene& = delete;
	auto operator=(scene&& s)->scene& = delete;
	~scene() = default;

	auto add_sphere(point center, double radius) -> void;
	
	auto render(image& image) const -> void;

private:
	std::vector<std::shared_ptr<intersectable>> _objects;

	auto add_object(std::shared_ptr<intersectable> object) -> void;
	auto create_primary_ray(size_t x, size_t y, const image& image) const ->ray;
};

