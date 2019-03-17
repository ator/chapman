#pragma once

class color
{
public:
	static const color WHITE;
	static const color BLACK;
	static const color GRAY;
	static const color RED;
	static const color GREEN;
	static const color BLUE;
	static const color YELLOW;
	static const color MAGENTA;

	color() = default;
	color(double red, double green, double blue);

	auto red() const -> double;
	auto green() const -> double;
	auto blue() const -> double;

	auto operator+=(const color& other) -> ::color&;
	auto operator+(const color& other) const -> ::color;
	auto operator*(const color& other) const->::color;
	auto operator*(const color&& other) const->::color;
	auto operator*(double factor) const->color;

	auto length2() const -> double;
	auto length() const -> double;
	auto scale(double factor) const -> color;
	auto clamp() const->color;

private:
	double _red;
	double _green;
	double _blue;
};
