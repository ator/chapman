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
	static const color yellow;
	static const color magenta;

	color() = default;
	color(double red, double green, double blue);

	auto operator+=(const ::color& color) -> ::color&;
	auto operator*(const ::color&& color) const->::color;
	auto operator*(double factor) const->color;

	auto rgb() const -> unsigned int;
	static auto size()->std::streamsize;

private:
	double _red;
	double _green;
	double _blue;
};
