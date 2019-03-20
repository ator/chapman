#include <boost/math/constants/constants.hpp>

#include "intersectable.h"

intersectable::intersectable(std::shared_ptr<::material> material) :
	_material(std::move(material))
{}

auto intersectable::get_material() const -> std::shared_ptr<::material>
{
	return _material;
}
