#pragma once
#include <string>

class color
{
public:
	static const color white;
	static const color black;

	color() = default;
	explicit color(unsigned int rgb);
	color(unsigned char red, unsigned char green, unsigned char blue);
	
	auto data() const -> const char*;
	auto rgb() const -> unsigned int;
	static auto size() -> std::streamsize;

private:
	union
	{
		unsigned char _rgb[3];
		struct
		{
			unsigned char _red;
			unsigned char _green;
			unsigned char _blue;
		};
	};
};
