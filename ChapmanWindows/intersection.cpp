#include "intersection.h"

intersection::intersection(const double distance, std::shared_ptr<intersectable> object) :
	_distance(distance),
	_object(object)
{}

auto intersection::distance() const -> double
{
	return _distance;
}

auto intersection::object() const -> std::shared_ptr<intersectable>
{
	return _object;
}
