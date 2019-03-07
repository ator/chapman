#include "scene.h"

scene::scene(const int width, const int height) :
	_width(width),
	_height(height),
	_aspect_ratio(static_cast<double>(width) / height)
{}

scene::scene(const scene&& s) noexcept
{
	_width = s._width;
	_height = s._height;
}

auto scene::operator=(scene&& s) noexcept -> scene&
{
	_width = s._width;
	_height = s._height;
	return *this;
}

auto scene::width() const -> int
{
	return _width;
}

auto scene::height() const -> int
{
	return _height;
}

auto scene::aspect_ratio() const -> double
{
	return _aspect_ratio;
}

scene::iterator::iterator(const scene& scene, const int x, const int y) :
	_scene(scene), _x(x), _y(y)
{}

auto scene::iterator::operator++() -> iterator&
{
	if (_x < _scene.width() - 1)
	{
		_x++;
		update_ray();
	}
	else
	{
		if (_y < _scene.height() - 1)
		{
			_x = 0;
			_y++;
			update_ray();
		}
		else
		{
			_x = _scene.width();
			_y = _scene.height();
		}
	}
	return *this;
}

auto scene::iterator::operator++(int) -> iterator
{
	iterator previous = *this; ++(*this); return previous;
}

auto scene::iterator::operator==(iterator other) const -> bool
{
	return _x == other._x && _y == other._y;
}

auto scene::iterator::operator!=(iterator other) const -> bool
{
	return !(*this == other);
}

auto scene::iterator::operator*() const -> reference
{
	return _ray;
}

auto scene::iterator::update_ray() -> void
{
	const auto pixel_center_x = static_cast<double>(_x) + 0.5;
	const auto pixel_center_y = static_cast<double>(_y) + 0.5;

	const auto sensor_x = (pixel_center_x / _scene.width() * 2.0 - 1.0) * _scene.aspect_ratio();
	const auto sensor_y = 1.0 - pixel_center_y / _scene.height() * 2.0;

	vector3 direction(sensor_x, sensor_y, -1.0);
	_ray = { point::zero, direction.normalize() };
}

auto scene::begin() const -> iterator
{
	return { *this, 0, 0 };
}

auto scene::end() const -> iterator
{
	return { *this, _width, _height };
};
