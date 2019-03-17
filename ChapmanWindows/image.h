#pragma once
#include <string>
#include <vector>

#include "color.h"
#include <boost/thread/mutex.hpp>

class image
{
public:
	image(size_t width, size_t height);
	~image();

	auto width() const -> size_t;
	auto height() const -> size_t;
	auto aspect_ratio() const -> double;

	auto set_pixel(size_t x, size_t y, color color) -> void;
	auto get_pixel(size_t x, size_t y) const->color;
	auto write_to_disk(const std::string& filename, bool normalize_colors = false) const -> void;

private:
	static const int MAX_COLOR_VALUE = 255;
	const size_t _width;
	const size_t _height;
	const double _aspect_ratio;
	color** _pixels;
	double _max_color;
	boost::mutex _pixels_mutex;

	auto write_color_component(std::ofstream& file, double component) const -> void;
};

