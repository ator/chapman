#include <cmath>

#include "color.h"

const color color::white(1.0, 1.0, 1.0);
const color color::black(0, 0, 0);
const color color::red(1.0, 0, 0);
const color color::green(0, 1.0, 0);
const color color::blue(0, 0, 1.0);

color::color(const double red, const double green, const double blue) :
	_red(red),
	_green(green),
	_blue(blue)
{}

auto color::operator*(const double factor) const -> color
{
	const auto red = _red * factor;
	const auto green = _green * factor;
	const auto blue = _blue * factor;
	return {red, green, blue};
}

auto color::rgb() const -> unsigned int
{
	const auto red = static_cast<unsigned int>(255 * std::fmin(_red,1.0));
	const auto green = static_cast<unsigned int>(255 * ::fmin(_green, 1.0));
	const auto blue = static_cast<unsigned int>(255 * ::fmin(_blue, 1.0));
	return (blue << 8 | green) << 8 | red;
}

auto color::size() -> std::streamsize
{
	return 3;
}
