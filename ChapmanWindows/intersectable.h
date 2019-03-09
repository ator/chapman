#pragma once

#include <boost/optional.hpp>

#include "ray.h"
#include "intersection.h"

class intersectable
{
public:
	intersectable() = default;
	intersectable(const intersectable& other) = delete;
	intersectable(intersectable&& other) = delete;
	auto operator=(const intersectable& other)->intersectable& = delete;
	auto operator=(intersectable&& other)->intersectable& = delete;
	virtual ~intersectable() = default;

	virtual auto intersects(const ray& ray) const -> boost::optional<intersection> = 0;
};
