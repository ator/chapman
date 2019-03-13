#pragma once
#include <string>

class color
{
public:
	static const color white;
	static const color black;
	static const color gray;
	static const color red;
	static const color green;
	static const color blue;
	static const color yellow;
	static const color magenta;

	color() = default;
	color(double red, double green, double blue);

	auto operator+=(const ::color& other) -> ::color&;
	auto operator+(const ::color& other) const -> ::color;
	auto operator*(const ::color& other) const->::color;
	auto operator*(const ::color&& other) const->::color;
	auto operator*(double factor) const->color;

	auto length2() const -> double;
	auto length() const -> double;
	auto scale(double factor) const -> color;
	auto clamp() const->color;

	auto rgb() const -> unsigned int;
	static auto size()->std::streamsize;

private:
	double _red;
	double _green;
	double _blue;
};
