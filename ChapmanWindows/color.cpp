#include <cmath>

#include "color.h"

const color color::white(1.0, 1.0, 1.0);
const color color::black(0, 0, 0);
const color color::gray(0.5, 0.5, 0.5);
const color color::red(1.0, 0, 0);
const color color::green(0, 1.0, 0);
const color color::blue(0, 0, 1.0);
const color color::yellow(1.0, 1.0, 0);
const color color::magenta(0, 1.0, 1.0);

color::color(const double red, const double green, const double blue) :
	_red(red),
	_green(green),
	_blue(blue)
{}

auto color::operator+=(const ::color& other) -> ::color&
{
	_red += other._red;
	_green += other._green;
	_blue += other._blue;
	return *this;
}

auto color::operator*(const ::color& other) const -> ::color
{
	const auto red = _red * other._red;
	const auto green = _green * other._green;
	const auto blue = _blue * other._blue;
	return color({ red, green, blue }).clamp();
}

auto color::operator*(const ::color&& other) const -> ::color
{
	const auto red = _red * other._red;
	const auto green = _green * other._green;
	const auto blue = _blue * other._blue;
	return color({ red, green, blue }).clamp();
}

auto color::operator*(const double factor) const -> color
{
	const auto red = _red * factor;
	const auto green = _green * factor;
	const auto blue = _blue * factor;
	return { red, green, blue };
}

auto color::rgb() const -> unsigned int
{
	const auto red = static_cast<unsigned int>(255 * _red);
	const auto green = static_cast<unsigned int>(255 * _green);
	const auto blue = static_cast<unsigned int>(255 * _blue);
	return (blue << 8 | green) << 8 | red;
}

auto color::size() -> std::streamsize
{
	return 3;
}

auto color::clamp() const -> color
{
	const auto red = std::fmax(std::fmin(1.0, _red), 0.0);
	const auto green = std::fmax(std::fmin(1.0, _green), 0.0);
	const auto blue = std::fmax(std::fmin(1.0, _blue), 0.0);
	return {red, green, blue};
}
