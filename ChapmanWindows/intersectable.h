#pragma once
#include "ray.h"

class intersectable
{
public:
	intersectable() = default;
	intersectable(const intersectable& other) = delete;
	intersectable(intersectable&& other) = delete;
	auto operator=(const intersectable& other)->intersectable& = delete;
	auto operator=(intersectable&& other)->intersectable& = delete;
	virtual ~intersectable() = default;

	virtual auto intersects(const ray& ray) const -> bool = 0;
};
