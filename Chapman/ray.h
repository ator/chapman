#pragma once
#include <iostream>

#include "point.h"
#include "vector3.h"

class ray
{
public:
	ray() = default;
	ray(point origin, vector3 direction);
	ray(const ray& r) = default;
	ray(const ray&& r) noexcept;
	auto operator=(const ray& r)->ray& = default;
	auto operator=(ray&& r)noexcept->ray&;
	~ray() = default;

	auto origin() const->const point&;
	auto direction() const->const vector3&;

	friend auto operator<<(std::ostream& os, const ray& r) -> std::ostream&;

private:
	point _origin{};
	vector3 _direction{};
};

inline std::ostream& operator<<(std::ostream& os, const ray& r)
{
	os << r._origin << "->" << r._direction;
	return os;
}
