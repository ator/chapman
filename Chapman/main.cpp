#include <iostream>
#include "scene.h"

int main()
{
	std::cout << "Chapman!" << std::endl;
	scene scene(10, 10);
	for (auto& ray : scene)
	{
		std::cout << ray << std::endl;
	}
}
