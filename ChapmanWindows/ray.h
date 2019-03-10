#pragma once

#include "vector3.h"

class ray
{
public:
	ray() = default;
	ray(vector3 origin, vector3 direction);
	ray(const ray& r) = default;
	ray(const ray&& r) noexcept;
	auto operator=(const ray& r)->ray& = default;
	auto operator=(ray&& r)noexcept->ray&;
	~ray() = default;

	auto origin() const->const vector3&;
	auto direction() const->const vector3&;

private:
	vector3 _origin{};
	vector3 _direction{};
};
