#include <iostream>

#include <boost/program_options.hpp>

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
		scene scene(35);
		scene.add_sphere({ 0, 0, -4 }, 2, color::red);
		scene.add_sphere({ 1, -1, -4 }, 2, color::green);
		scene.add_sphere({ -1, -1, -4 }, 2, color::blue);
		scene.add_sphere({ 1, 1, -4 }, 2, color(1.0, 0.0, 1.0));
		scene.add_sphere({ -1, 1, -4 }, 2, color(1.0, 1.0, 0.0));
		scene.add_plane({ 0, -3, 0 }, {0, -1, 0}, color(0.0, 1.0, 1.0));
		scene.add_directional_light({ 1, 1, -1 }, color::white, 1.0);

		std::cout << "Rendering " << width << "x" << height << " pixels..." << std::endl;
		image image(width, height);
		scene.render(image);

		std::cout << "Saving image to " << filename << "..." << std::endl;
		//image.write_to_screen();
		image.write_to_disk(filename);

		std::cout << "Done!" << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
}
