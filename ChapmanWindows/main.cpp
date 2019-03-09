#include <iostream>
#include "scene.h"

int main()
{
	try
	{
		std::cout << "Chapman v1.0" << std::endl;

		std::cout << "Loading scene..." << std::endl;
		scene scene(35);
		scene.add_sphere({ 0, 0, -4 }, 2, color::red);
		scene.add_sphere({ 1, -1, -4 }, 2, color::green);
		scene.add_sphere({ -1, -1, -4 }, 2, color::blue);
		scene.add_sphere({ 1, 1, -4 }, 2, color(1.0, 0.0, 1.0));
		scene.add_sphere({ -1, 1, -4 }, 2, color(1.0, 1.0, 0.0));

		std::cout << "Rendering..." << std::endl;
		image image(512, 512);
		scene.render(image);

		std::cout << "Saving image..." << std::endl;
		//image.write_to_screen();
		image.write_to_disk("test.ppm");

		std::cout << "Done!" << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
}
