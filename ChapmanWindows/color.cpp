#include <cmath>

#include "color.h"

const color color::WHITE(1.0, 1.0, 1.0);
const color color::BLACK(0, 0, 0);
const color color::GRAY(0.5, 0.5, 0.5);
const color color::RED(1.0, 0, 0);
const color color::GREEN(0, 1.0, 0);
const color color::BLUE(0, 0, 1.0);
const color color::YELLOW(1.0, 1.0, 0);
const color color::MAGENTA(0, 1.0, 1.0);

color::color(const double red, const double green, const double blue) :
	_red(red),
	_green(green),
	_blue(blue)
{}

auto color::red() const -> double
{
	return _red;
}

auto color::green() const -> double
{
	return _green;
}

auto color::blue() const -> double
{
	return _blue;
}

auto color::operator+=(const ::color& other) -> ::color&
{
	_red += other._red;
	_green += other._green;
	_blue += other._blue;
	return *this;
}

auto color::operator+(const ::color& other) const -> ::color
{
	const auto red = _red + other._red;
	const auto green = _green + other._green;
	const auto blue = _blue + other._blue;
	return { red, green, blue };
}

auto color::operator*(const ::color& other) const -> ::color
{
	const auto red = _red * other._red;
	const auto green = _green * other._green;
	const auto blue = _blue * other._blue;
	return { red, green, blue };
}

auto color::operator*(const ::color&& other) const -> ::color
{
	const auto red = _red * other._red;
	const auto green = _green * other._green;
	const auto blue = _blue * other._blue;
	return { red, green, blue };
}

auto color::operator*(const double factor) const -> color
{
	const auto red = _red * factor;
	const auto green = _green * factor;
	const auto blue = _blue * factor;
	return { red, green, blue };
}

auto color::operator/(double factor) const -> color
{
	const auto red = _red / factor;
	const auto green = _green / factor;
	const auto blue = _blue / factor;
	return { red, green, blue };
}

auto color::length2() const -> double
{
	return _red * _red + _green * _green + _blue * _blue;
}

auto color::length() const -> double
{
	return std::sqrt(length2());
}

auto color::scale(const double factor) const -> color
{
	const auto red = _red / factor;
	const auto green = _green / factor;
	const auto blue = _blue / factor;
	return { red, green, blue };
}

auto color::clamp() const -> color
{
	const auto red = std::fmax(std::fmin(1.0, _red), 0.0);
	const auto green = std::fmax(std::fmin(1.0, _green), 0.0);
	const auto blue = std::fmax(std::fmin(1.0, _blue), 0.0);
	return { red, green, blue };
}
