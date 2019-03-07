#pragma once
#include <iterator>
#include "ray.h"

class scene
{
public:
	scene() = default;
	scene(int width, int height);
	scene(const scene& s) = default;
	scene(const scene&& s) noexcept;
	auto operator=(const scene& s) noexcept->scene& = default;
	auto operator=(scene&& s) noexcept->scene&;
	~scene() = default;

	auto width() const -> int;
	auto height() const -> int;
	auto aspect_ratio() const -> double;

	class iterator : public std::iterator<std::input_iterator_tag, const ray>
	{
	public:
		iterator(const scene& scene, int x, int y);

		iterator& operator++();
		iterator operator++(int);
		bool operator==(iterator other) const;
		bool operator!=(iterator other) const;
		auto operator*() const -> reference;

	private:
		const scene& _scene;
		int _x;
		int _y;
		ray _ray;
		
		auto update_ray() -> void;
	};

	auto begin() const -> iterator;
	auto end() const -> iterator;

private:
	int _width{};
	int _height{};
	double _aspect_ratio{};
};

