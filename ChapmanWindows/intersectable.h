#pragma once

#include <boost/optional.hpp>

#include "ray.h"
#include "material.h"

class intersection;

class intersectable
{
public:
	explicit intersectable(std::shared_ptr<material> material);
	intersectable(const intersectable& other) = delete;
	intersectable(intersectable&& other) = delete;
	auto operator=(const intersectable& other)->intersectable& = delete;
	auto operator=(intersectable&& other)->intersectable& = delete;
	virtual ~intersectable() = default;

	auto material() const -> std::shared_ptr<material>;

	virtual auto intersection_distance(const ray& ray) const -> boost::optional<double> = 0;
	virtual auto surface_normal(const vector3& hit_point) const->vector3 = 0;

private:
	std::shared_ptr<::material> _material;
};
