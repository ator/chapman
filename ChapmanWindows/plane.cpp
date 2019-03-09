#include "plane.h"

plane::plane(const point center, const vector3 normal, const color color) :
	_center(center),
	_normal(normal),
	_color(color)
{}

auto plane::intersects(const ray& ray) const -> boost::optional<intersection>
{
	const auto denominator = _normal * ray.direction();
	if (denominator > 1e-6)
	{
		const auto v = _center - ray.origin();
		const auto distance = v * _normal / denominator;
		if (distance >= 0.0)
		{
			return { { distance, _color} };
		}
	}

	return {};
}
