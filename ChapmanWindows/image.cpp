#include <cassert>
#include <fstream>

#include "image.h"
#include <iostream>
#include <iomanip>

image::image(size_t width, size_t height) :
	_width(width),
	_height(height),
	_aspect_ratio(static_cast<double>(width) / height)
{
	_pixels.resize(height);
	for (auto& row : _pixels)
	{
		row.resize(width);
	}
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
}

auto image::write_to_disk(const std::string& filename) const -> void
{
	std::ofstream file(filename, std::ios::out | std::ios::binary);
	if (file)
	{
		const auto max_color_value = 255;
		file << "P6\n " << _width << "\n " << _height << "\n " << max_color_value << "\n";
		for (auto& row : _pixels)
		{
			file.write(reinterpret_cast<const char*>(row.data()), row.size() * color::size());
			//for (auto& pixel : row)
			//{
			//	file.write(pixel.data(), color::size());
			//}
		}

		file.close();
	}
}

auto image::write_to_screen() const -> void
{
	for (auto& row : _pixels)
	{
		for (auto& pixel : row)
		{
			std::cout << std::setw(6) << std::hex << pixel.rgb() << " ";
		}
		std::cout << std::endl;
	}
}
