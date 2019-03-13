#include <iostream>

#include <boost/program_options.hpp>
#include <boost/math/constants/constants.hpp>

#include "scene.h"

int main(const int argc, const char* argv[])
{
	try
	{
		std::cout << "Chapman v1.0" << std::endl;

		size_t width;
		size_t height;
		std::string filename;
		boost::program_options::options_description description("Usage");
		description.add_options()
			("width", boost::program_options::value<size_t>(&width)->default_value(1900), "Image width")
			("height", boost::program_options::value<size_t>(&height)->default_value(1080), "Image height")
			("output", boost::program_options::value<std::string>(&filename)->default_value("image.ppm"), "Output filename");
		boost::program_options::variables_map vm;
		store(parse_command_line(argc, argv, description), vm);
		notify(vm);

		std::cout << "Loading scene..." << std::endl;
		scene scene(90);
		
		auto number_of_spheres = 90;
		double radius = 4;
		for (auto i = 0; i < number_of_spheres; ++i)
		{
			const auto angle = 2 * boost::math::constants::pi<double>() / number_of_spheres * i;
			const auto x = radius * std::cos(angle * 4);
			const auto y = 8.0 / number_of_spheres * i - 4;
			const auto z = radius * std::sin(angle * 4) - 11;
			const auto r = 0.5 + 0.5 * std::cos(angle);
			const auto g = 0.5 + 0.5 * std::sin(angle * 2);
			const auto b = 0.5 + 0.5 * std::sin(-angle) * std::cos(-angle);
			scene.add_sphere({ x, y, z }, 0.25, color(r, g, b).clamp());
		}

		scene.add_plane({ 0, -3.5, 0 }, {0, 1, 0}, color::white);
		scene.add_plane({ 0, 3.5, 0 }, {0, -1, 0}, color::white);

		scene.add_directional_light({ 1, 0, -0.5 }, color::white, 1.0);
		scene.add_directional_light({ -1, 0, -0.5 }, color::white, 1.0);
		scene.add_point_light({ 0, 2.5, -11 }, color::white, 30);
		scene.add_point_light({ 10, 1, -1 }, color::white, 10);

		std::cout << "Rendering " << width << "x" << height << " pixels..." << std::endl;
		image image(width, height);
		scene.render(image);

		std::cout << "Saving image to " << filename << "..." << std::endl;
		//image.write_to_screen();
		image.write_to_disk(filename, false);

		std::cout << "Done!" << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
}
