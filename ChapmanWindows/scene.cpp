#include "scene.h"
#include "sphere.h"

auto scene::add_sphere(point center, double radius) -> void
{
	add_object(std::make_shared<::sphere>(center, radius));
}

auto scene::render(image& image) const -> void
{
	for (size_t y = 0; y < image.height(); ++y)
	{
		for (size_t x = 0; x < image.width(); ++x)
		{
			auto primary_ray = create_primary_ray(x, y, image);
			auto hit = false;
			for (auto& object : _objects)
			{
				if (object->intersects(primary_ray))
				{
					hit = true;
					break;
				}
			}
			const auto color = hit ? color::white : color::black;
			image.set_pixel(x, y, color);
		}
	}
}

auto scene::add_object(std::shared_ptr<intersectable> object) -> void
{
	_objects.emplace_back(std::move(object));
}

auto scene::create_primary_ray(const size_t x, const size_t y, const image& image) const -> ray
{
	const auto pixel_center_x = static_cast<double>(x) + 0.5;
	const auto pixel_center_y = static_cast<double>(y) + 0.5;

	const auto sensor_x = (pixel_center_x / image.width() * 2.0 - 1.0) * image.aspect_ratio();
	const auto sensor_y = 1.0 - pixel_center_y / image.height() * 2.0;

	vector3 direction(sensor_x, sensor_y, -1.0);
	return { point::zero, direction.normalize() };
}
