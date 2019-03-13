#pragma once
#include <string>
#include <vector>

#include "color.h"

class image
{
public:
	image(size_t width, size_t height);

	auto width() const -> size_t;
	auto height() const -> size_t;
	auto aspect_ratio() const -> double;

	auto set_pixel(size_t x, size_t y, color color) -> void;
	auto write_to_disk(const std::string& filename, bool normalize_colors = false) const -> void;
	auto write_to_screen() const -> void;

private:
	const size_t _width;
	const size_t _height;
	const double _aspect_ratio;
	std::vector<std::vector<color>> _pixels;
	double _max_color;
};

