#pragma once
#include <string>

class color
{
public:
	static const color white;
	static const color black;
	static const color red;
	static const color green;
	static const color blue;

	color() = default;
	color(double red, double green, double blue);

	auto operator*(double factor) const->color;

	auto rgb() const -> unsigned int;
	static auto size()->std::streamsize;

private:
	double _red;
	double _green;
	double _blue;
};
