#include <iostream>
#include "scene.h"

int main()
{
	try
	{
		std::cout << "Chapman v1.0" << std::endl;

		std::cout << "Loading scene..." << std::endl;
		scene scene;
		scene.add_sphere({ 0, 0, 2 }, 1);
		scene.add_sphere({ 1, -1, 2.5 }, 0.75);
		scene.add_sphere({ -1, -1, 2.5 }, 0.75);

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
