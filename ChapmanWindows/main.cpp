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
		scene scene(90);
		
		scene.add_sphere({  0,  0, -11 }, 1.5, color::red);
		
		scene.add_sphere({ -2, -2, -12 }, 1, color::green);
		scene.add_sphere({  2, -2, -12 }, 1, color::blue);
		scene.add_sphere({ -2,  2, -12 }, 1, color::yellow);
		scene.add_sphere({  2,  2, -12 }, 1, color::magenta);

		scene.add_sphere({ -2, -2, -10 }, 1, color::magenta);
		scene.add_sphere({  2, -2, -10 }, 1, color::yellow);
		scene.add_sphere({ -2,  2, -10 }, 1, color::blue);
		scene.add_sphere({  2,  2, -10 }, 1, color::green);

		scene.add_plane({ 0, -3, 0 }, {0, 1, 0}, color::gray);

		scene.add_directional_light({ 1, -1, -0.5 }, color::white, 2.0);
		scene.add_directional_light({ -1, -0.5, -1 }, color::white, 1.0);

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
