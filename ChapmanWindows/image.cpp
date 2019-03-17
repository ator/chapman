#include <cassert>
#include <fstream>
#include <iomanip>

#include "image.h"
#include <mutex>
#include <boost/thread/lock_algorithms.hpp>

image::image(const size_t width, const size_t height) :
	_width(width),
	_height(height),
	_aspect_ratio(static_cast<double>(width) / height),
	_max_color(0)
{
	_pixels = new color*[height];
	for (size_t y = 0; y < height; ++y)
	{
		_pixels[y] = new color[width];
	}
}

image::~image()
{
	for (size_t y = 0; y < _height; ++y)
	{
		delete[] _pixels[y];
	}
	delete[] _pixels;
}

auto image::width() const -> size_t
{
	return _width;
}

auto image::height() const -> size_t
{
	return _height;
}

auto image::aspect_ratio() const -> double
{
	return _aspect_ratio;
}

auto image::set_pixel(const size_t x, const size_t y, const color color) -> void
{
	assert(x < _width);
	assert(y < _height);
	_pixels[y][x] = color;
	_max_color = std::fmax(color.length2(), _max_color);
}

auto image::get_pixel(const size_t x, const size_t y) const -> color
{
	return _pixels[y][x];
}

auto image::write_to_disk(const std::string& filename, const bool normalize_colors) const -> void
{
	std::ofstream file(filename, std::ios::out | std::ios::binary);
	if (file)
	{
		const auto color_factor = std::sqrt(_max_color);
		file << "P6\n" << _width << "\n" << _height << "\n" << MAX_COLOR_VALUE << "\n";

		for (size_t y = 0; y < _height; ++y)
		{
			for (size_t x = 0; x < _width; ++x)
			{
				auto pixel = _pixels[y][x];
				auto color = normalize_colors ? pixel.scale(color_factor) : pixel.clamp();
				write_color_component(file, color.red());
				write_color_component(file, color.green());
				write_color_component(file, color.blue());
			}
		}

		file.close();
	}
}

auto image::write_color_component(std::ofstream& file, const double component) const -> void
{
	const auto raw = static_cast<unsigned char>(component * MAX_COLOR_VALUE);
	file.write(reinterpret_cast<const char*>(&raw), 1);
}
