#include "color.h"

const color color::white(255, 255, 255);
const color color::black(0, 0, 0);

color::color(unsigned rgb) :
	_red((rgb & 0xFF0000) >> 16),
	_green((rgb & 0x00FF00) >> 8),
	_blue(rgb & 0x0000FF)
{}

color::color(const unsigned char red, const unsigned char green, const unsigned char blue) :
	_red(red),
	_green(green),
	_blue(blue)
{}

auto color::data() const -> const char*
{
	return reinterpret_cast<const char*>(_rgb);
}

auto color::rgb() const -> unsigned
{
	return (_red << 8 | _green) << 8 | _blue;
}

auto color::size() -> std::streamsize
{
	return 3;
}
